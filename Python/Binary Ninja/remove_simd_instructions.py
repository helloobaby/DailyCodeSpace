#Snippets test
#Backspace
from binaryninja.binaryview import BinaryView
from binaryninja.enums import DisassemblyOption
from binaryninja import function,Function,BasicBlock,LowLevelILInstruction,RegisterIndex,LowLevelILBasicBlock,LowLevelILIntrinsic
from binaryninja.function import DisassemblyTextLine
from binaryninja.lowlevelil import LowLevelILOperation,LowLevelILOperandType,ILRegister,LowLevelILReg
from binaryninja.architecture import Architecture

# 
st0_index=169
st7_index=176
# MMX
mm0_index=114
mm7_index=121
# SIMD
xmm0_index=178
xmm15_index=193


# 以线性的方式遍历function llir 
def Traversal_Function_llir(f:Function) -> list[LowLevelILInstruction]:
    for i in range(len(f.low_level_il)):
        instrution=f.low_level_il[i]
        print(instrution)

# operands
# mm2 = mm2 | mm3

#     =
#    / \
#   mm2 or
#      / \
#     mm2 mm3
# 	mm2
# 	LLIL_OR
# 		LLIL_REG
# 			mm2
# 		LLIL_REG
# 			mm3
# LowLevelILOperation.LLIL_SET_REG                
# <class 'binaryninja.lowlevelil.ILRegister'>
# <class 'binaryninja.lowlevelil.LowLevelILOr'>  

    #     =
    #    / \
    # mm4  _m_pcmpeqd
    #     / \
    #   mm4 mm1

# 层序遍历

def get_disassembly_text(bv:BinaryView,eip:int) -> DisassemblyTextLine:
    disassembly_text = bv.get_disassembly(eip)
    disassembly_text_line = DisassemblyTextLine(disassembly_text, eip)
    return disassembly_text_line
def traverse_IL(il, indent):
  if isinstance(il, LowLevelILInstruction):
    print ('\t'*indent + il.operation.name)
 
    for o in il.operands:
      traverse_IL(o, indent+1)
 
  else:
    print ('\t'*indent + str(il))

def is_simd_instruction(bv:BinaryView,llil:LowLevelILInstruction)->bool:
    if 'emms' in get_disassembly_text(bv,llil.address).tokens:
       return True
    try:
        for op1 in llil.operands:
            if isinstance(op1,ILRegister):
                if op1.info.index in range(st0_index,st7_index) or op1.info.index in range(mm0_index,mm7_index) or op1.info.index in range(xmm0_index,xmm15_index):
                    return True
                return False
            if isinstance(op1,list):
                for o in op1:
                    if o.info.index in range(st0_index,st7_index) or o.info.index in range(mm0_index,mm7_index) or o.info.index in range(xmm0_index,xmm15_index):
                        return True
                    return False
    except:
        pass
    return False

def remove_simd_instruction(bv:BinaryView,func:Function):
   for i in range(len(func.low_level_il)):
      llil = func.low_level_il[i]
      print(hex(llil.address))
      if is_simd_instruction(bv,llil):
         bv.convert_to_nop(llil.address)  #有个大问题，因为llil可能不是一条指令，一个basicblock


# 打印一条llir的信息 方便调试
def print_single_llir_test(index):
    llil:LowLevelILInstruction = current_function.low_level_il[index]
    print(is_simd_instruction(current_view,llil))
    traverse_IL(llil,0)
    


print('--'*32)
arch = Architecture['x86_64']
#Traversal_Function_llir(current_function)
print_single_llir_test(26)


remove_simd_instruction(current_view,current_function)

