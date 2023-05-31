//
// @file main.cpp in bin2llvmir
// @brief 原bin2llvmir是个lib,还需要改CMakeLists
// 

/*
mkdir build;cd build;
cmake .. -DCMAKE_INSTALL_PREFIX="" -G="Visual Studio 16 2019" -DRETDEC_ENABLE_BIN2LLVMIR=1 -DRETDEC_MSVC_STATIC_RUNTIME=0
*/

/*
以下函数去除操作flags的代码
translateAdd\translateXor

*/

#include <iomanip>
#include <algorithm>

// 把keystone的依赖去了,这b玩意老链接不正常
//#include <keystone/keystone.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
//https://llvm.org/docs/WritingAnLLVMNewPMPass.html
//#include <llvm/IR/PassManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Transforms/IPO/GlobalDCE.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>

#include "retdec/common/address.h"
#include "retdec/utils/conversion.h"
#include "retdec/utils/string.h"
#include "retdec/utils/io/log.h"
#include "retdec/utils/version.h"

#include "retdec/capstone2llvmir/capstone2llvmir.h"
#include "retdec/bin2llvmir/providers/asm_instruction.h"
#include "retdec/bin2llvmir/optimizations/asm_inst_remover/asm_inst_remover.h"
#include "retdec/bin2llvmir/optimizations/inst_opt/inst_opt_pass.h"
#include "retdec/bin2llvmir/optimizations/register_localization/register_localization.h"
#include "retdec/bin2llvmir/optimizations/phi_remover/phi_remover.h"

namespace llvm {
extern llvm::ModulePass *createGlobalDCEPass(); //GlobalDCE.cpp
extern Pass *createDeadInstEliminationPass(); //DCE.cpp
}
using namespace std;

struct Hello : public llvm::FunctionPass {
  static char ID;
  Hello() : FunctionPass(ID) {}

  bool runOnFunction(llvm::Function &FF) override {
    using namespace llvm;

    return false;
  }
};



char Hello::ID = 0;
static llvm::RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);


int main(int argc, char *argv[]) {
  llvm::LLVMContext ctx;
  llvm::Module module("test", ctx);

  auto *f = llvm::Function::Create(
      llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false),
      llvm::GlobalValue::ExternalLinkage, "root", &module);

  llvm::BasicBlock::Create(module.getContext(), "entry", f);

  llvm::IRBuilder<> irb(&f->front());

  auto *ret = irb.CreateRetVoid();
  irb.SetInsertPoint(ret);

  std::unique_ptr<retdec::capstone2llvmir::Capstone2LlvmIrTranslator> c2l;
  try {
    c2l = retdec::capstone2llvmir::Capstone2LlvmIrTranslator::createArch(
        CS_ARCH_X86, &module, CS_MODE_32, CS_MODE_LITTLE_ENDIAN);

    std::vector<uint8_t> v = {
        0x8D, 0x55, 0xE8, 0xBB, 0xF6, 0x00, 0x00, 0x00, 0x31, 0xE8, 0x89,
        0x45, 0xF0, 0xC7, 0x45, 0xE8, 0xC6, 0x00, 0x00, 0x00, 0xBF, 0x27,
        0xDE, 0x04, 0x10, 0xB8, 0xff, 0xff, 0xff, 0xff, 0x2D, 0xF3, 0x00,
        0x00, 0x00, 0xf7, 0xd0, 0x8b, 0x0a, 0x29, 0xc8,0x01,0xc7,0xC7,0x45,0xEC,0xD0,0x00,0x00,0x00,
        0xFF,0xE7
    };

    // 生成的llvm ir中@0存放是这个Address参数
    // store volatile i64 0, i64* @0
    c2l->translate(v.data(), v.size(), 0, irb);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    assert(false);
  } catch (...) {
    std::cerr << "Some unhandled exception" << std::endl;
  }

  // create fpm and mpm
  std::unique_ptr<llvm::legacy::FunctionPassManager> fpm =
      std::make_unique<llvm::legacy::FunctionPassManager>(&module);
  llvm::legacy::PassManager mpm;


  Hello *HelloPass = new Hello;  //Pass必须是在堆上分配的,否则析构的时候会崩
  fpm->add(HelloPass);  // 自己写的测试用的llvm pass

  // 合并指令
  // 比如mov ebx,1;add ebx 1; -> mov ebx,2
  fpm->add(llvm::createInstructionCombiningPass());

  // 删除一些无用的死代码
  fpm->add(llvm::createDeadInstEliminationPass());


  // 指令地址方面的优化  ir上表现为!insn.addr
  retdec::bin2llvmir::AsmInstruction ai;
  ai.setLlvmToAsmGlobalVariable(&module,c2l->getAsm2LlvmMapGlobalVariable());
  retdec::bin2llvmir::AsmInstructionRemover *air = new retdec::bin2llvmir::AsmInstructionRemover;
  mpm.add(air);
 
  //retdec::bin2llvmir::PhiRemover *Phi = new retdec::bin2llvmir::PhiRemover;
  //mpm.add(Phi);
  
  // 个别指令进行优化,没大用
  //retdec::bin2llvmir::InstructionOptimizer *IO =
  //    new retdec::bin2llvmir::InstructionOptimizer;
  //mpm.add(IO);

 /* retdec::bin2llvmir::RegisterLocalization *RL =
      new retdec::bin2llvmir::RegisterLocalization;
  mpm.add(RL);*/

  // 删除没用到的全局变量
  // 因为可能有些优化pass会删除其中的全局变量的引用,所以这个优化要放到后面的
  mpm.add(llvm::createGlobalDCEPass());  

  mpm.run(module);
  fpm->run(*f);

  for (llvm::inst_iterator I = llvm::inst_begin(f), E = llvm::inst_end(f);
       I != E;I++) {
    auto storeInsn = llvm::dyn_cast<llvm::StoreInst>(&*I);
    if (storeInsn) {
      //storeInsn->print(llvm::outs());
      
    }
  }


  std::error_code ec;
  llvm::raw_fd_ostream out("main.ll", ec, llvm::sys::fs::F_None);
  //std::printf("####################################\n");
  module.print(llvm::outs(), nullptr);
  module.print(out, nullptr);

  std::system("ll2s.bat");
  std::system("s2o.bat");

  return EXIT_SUCCESS;
}
