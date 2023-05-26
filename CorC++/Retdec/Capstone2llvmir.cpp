/* 
Build:
mkdir build;cd build;
cmake .. -DCMAKE_INSTALL_PREFIX="" -G="Visual Studio 16 2019" -DRETDEC_ENABLE_CAPSTONE2LLVMIRTOOL=1 -DRETDEC_MSVC_STATIC_RUNTIME=0

(1)Visual Studio Debug X64 编译,keystone用的vcpkg安装的,deps下面的好像有点问题,链接不上。这里要注意sln项目设置里的lib输入路径大于vcpkg的优先级,也就是说要保证项目里没有keystone lib的搜索路径,不然是不会链接到vcpkg安装的lib里的。
(2)每次Cmake生成完后,vcpkg都要卸载安装一下
*/


//https://github.com/avast/retdec

#include <iomanip>
#include <algorithm>

#include <keystone/keystone.h>
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

namespace llvm {
extern llvm::ModulePass *createGlobalDCEPass();
extern Pass *createDeadInstEliminationPass(); //DCE.cpp
}
using namespace std;

int init_ks(ks_arch arch, int mode, int syntax);
std::vector<uint8_t> util_assembly_to_bytes_32(const std::string &insn_str);

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

    //auto *internal_function_test = llvm::Function::Create(
    //  llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false),
    //  llvm::GlobalValue::InternalLinkage, "im_internal", &module);

  llvm::BasicBlock::Create(module.getContext(), "entry", f);

  llvm::IRBuilder<> irb(&f->front());

  auto *ret = irb.CreateRetVoid();
  irb.SetInsertPoint(ret);

  try {
    auto c2l = retdec::capstone2llvmir::Capstone2LlvmIrTranslator::createArch(
        CS_ARCH_X86, &module, CS_MODE_32, CS_MODE_LITTLE_ENDIAN);

    auto v = util_assembly_to_bytes_32("mov ebx,1");

    // v.clear();

    auto tv = util_assembly_to_bytes_32("add ebx,1");
    v.insert(v.end(), tv.begin(), tv.end());

    tv = util_assembly_to_bytes_32("nop");
    v.insert(v.end(), tv.begin(), tv.end());

    tv = util_assembly_to_bytes_32("mov eax,ebx");
    v.insert(v.end(), tv.begin(), tv.end());


    // 生成的llvm ir中@0存放是这个Address参数
    // store volatile i64 0, i64* @0
    c2l->translate(v.data(), v.size(), 0, irb);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    assert(false);
  } catch (...) {
    std::cerr << "Some unhandled exception" << std::endl;
  }

  std::unique_ptr<llvm::legacy::FunctionPassManager> fpm = std::make_unique<llvm::legacy::FunctionPassManager>(&module);

  Hello *HelloPass = new Hello; //必须是在堆上分配的
  llvm::legacy::PassManager mpm;
  
  fpm->add(HelloPass); // 自己写的测试用的llvm pass
  // 合并指令
  // 比如mov ebx,1;add ebx 1; -> mov ebx,2
  fpm->add(llvm::createInstructionCombiningPass());   
  // 删除一些无用的死代码
  fpm->add(llvm::createDeadInstEliminationPass());
  fpm->run(*f);

  mpm.add(llvm::createGlobalDCEPass()); // 没用到的全局变量都删了
  mpm.run(module);

  for (llvm::inst_iterator I = llvm::inst_begin(f), E = llvm::inst_end(f);
       I != E;I++) {
    //TODO
  }


  std::error_code ec;
  llvm::raw_fd_ostream out("main.ll", ec, llvm::sys::fs::F_None);
  printf("####################################\n");
  module.print(llvm::outs(), nullptr);
  module.print(out, nullptr);

  system("ll2s.bat");system("s2o.bat");

  return EXIT_SUCCESS;
}


ks_engine *ks = nullptr;
// https://github.com/keystone-engine/keystone/blob/master/samples/sample.c
int init_ks(ks_arch arch, int mode, int syntax) {
  ks_err err;

  err = ks_open(arch, mode, &ks);
  if (err != KS_ERR_OK) {
    return -1;
  }

  if (syntax) ks_option(ks, KS_OPT_SYNTAX, syntax);

  return KS_ERR_OK;
}
std::vector<uint8_t> util_assembly_to_bytes_32(const std::string &insn_str) {
  if (!ks) {
    int r = init_ks(KS_ARCH_X86, KS_MODE_32, 1);
    if (r != KS_ERR_OK) {  // error
      printf(">> keystone init failed\n");
      exit(0);
    }
  }

  ks_err err;
  size_t count;
  unsigned char *encode;
  size_t size;
  int r = ks_asm(ks, insn_str.c_str(), 0, &encode, &size, &count);
  if (r != KS_ERR_OK) {
    printf(">> ks_asm failed\n");
    exit(0);
  }
  uint8_t *uencode = encode;
  return std::vector<uint8_t>(uencode,uencode+size);
}
