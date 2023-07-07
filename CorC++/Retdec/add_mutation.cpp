//
// @file main.cpp in bin2llvmir
// @brief 原bin2llvmir是个lib,还需要改CMakeLists
// 

// 2023.6.21
// 项目用cmake编译需要增加包含目录D:\workspace\retdec\build\external\src\llvm-project\include
// Intelligence才能正常工作

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
#include <llvm/IR/InlineAsm.h>

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

 struct GlobalVariablePass : public llvm::FunctionPass
{
	static char ID;

	GlobalVariablePass(): llvm::FunctionPass(ID) {}

	bool runOnFunction(llvm::Function& F) override
	{
		
		// 遍历全局变量
		for (auto& global: F.getParent()->globals())
		{
			// 打印全局变量的名称
			llvm::outs() << "Global Variable: " << global.getName() << "\n";
		}
		return false;
	}
};



char Hello::ID = 0;
static llvm::RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

char GlobalVariablePass::ID = 0;
static llvm::RegisterPass<GlobalVariablePass>
	Y("Global", "Hello World Pass", false /* Only looks at CFG */, false /* Analysis Pass */);


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
        CS_ARCH_X86, &module, CS_MODE_64, CS_MODE_LITTLE_ENDIAN);


//add mutation
//push rax
//not rax
//sub rcx, rax
//pop rax
//sub rcx, 1

	unsigned char opcodes[] = {
		0x50,
		0x48,
		0xf7,
		0xd0,
		0x48,
		0x29,
		0xc1,
		0x58,
		0x48,
		0x83,
		0xe9,
		0x01,
	};
	std::vector<uint8_t> v(opcodes, opcodes + sizeof(opcodes));

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

  //GlobalVariablePass* GlobalPass = new GlobalVariablePass;
  //fpm->add(GlobalPass);
  
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

  //  call void asm sideeffect inteldialect "mov eax,$0", "r"(i32* @eax)
  //  call void asm sideeffect inteldialect "mov ebx,$0", "r"(i32 * @ebx)
  

  // 


  // 将全局变量映射到物理架构的寄存器上
  llvm::InlineAsm* inlineAsm = llvm::InlineAsm::get(
	  llvm::FunctionType::get(irb.getVoidTy(),irb.getInt32Ty(), false),
	  "mov rax,$0",
	  "r",
	  true,
	  false,
	  llvm::InlineAsm::AD_Intel);
  irb.CreateCall(inlineAsm, c2l->getRegister(X86_REG_RAX));

    inlineAsm = llvm::InlineAsm::get(
	  llvm::FunctionType::get(irb.getVoidTy(), irb.getInt32Ty(), false),
	  "mov rcx,$0",
	  "r",
	  true,
	  false,
	  llvm::InlineAsm::AD_Intel);
  irb.CreateCall(inlineAsm, c2l->getRegister(X86_REG_RCX));

      inlineAsm = llvm::InlineAsm::get(
	  llvm::FunctionType::get(irb.getVoidTy(), irb.getInt32Ty(), false),
	  "mov rsp,$0",
	  "r",
	  true,
	  false,
	  llvm::InlineAsm::AD_Intel);
  irb.CreateCall(inlineAsm, c2l->getRegister(X86_REG_RSP));


  std::error_code ec;
  llvm::raw_fd_ostream out("main.ll", ec, llvm::sys::fs::F_None);
  //std::printf("####################################\n");
  module.print(llvm::outs(), nullptr);
  module.print(out, nullptr);

  // x64 compile
  system("opt.exe -O3 main.ll -o main_opt.bc");
  system("llc.exe main_opt.bc -x86-asm-syntax=intel");
  system("clang.exe -c main_opt.bc");  

  return EXIT_SUCCESS;
}
