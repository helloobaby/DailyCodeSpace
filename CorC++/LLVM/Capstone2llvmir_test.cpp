#include <iostream>
#include <iomanip>
#include <memory>

// vcpkg install capstone
// vcpkg install keystone
#include <keystone/keystone.h>

// 不用自己编译
// https://ziglang.org/deps/llvm%2bclang%2blld-13.0.1-x86_64-windows-msvc-release-mt.tar.xz
// vs2019 X64 Release编译可用,其他IDE版本未测试
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

#include "../include/retdec/capstone2llvmir/capstone2llvmir.h"

//https://shell-storm.org/online/Online-Assembler-and-Disassembler/?inst=mov+eax%2C1&arch=x86-64&as_format=carray#assembly
unsigned char opcodes[] = {
    0xb8, 0x01, 0x00, 0x00, 0x00, 
};

int main()
{
    llvm::LLVMContext ctx;
	
	// module不用unique的话会出内存问题
	auto module = std::make_unique<llvm::Module>("main.c",ctx);


    auto* f = llvm::Function::Create(
			llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false),
			llvm::GlobalValue::ExternalLinkage,
			"root",
			*module);

	llvm::BasicBlock::Create(module->getContext(), "entry", f);
	llvm::IRBuilder<> irb(&f->front());

	auto* ret = irb.CreateRetVoid();
	irb.SetInsertPoint(ret);


	try
	{
		auto c2l = retdec::capstone2llvmir::Capstone2LlvmIrTranslator::createArch(
				CS_ARCH_X86,
				module.get(),
				CS_MODE_32, //32位程序
				CS_MODE_LITTLE_ENDIAN);
		c2l->translate(opcodes,5, 0x10000000, irb);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		assert(false);
	}
	catch (...)
	{
		std::cerr << "Some unhandled exception" << std::endl;
	}

	// 控制台打印ir
	module->print(llvm::outs(), nullptr);

    return 0;
}

