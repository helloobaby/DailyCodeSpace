#Snippets test
#

# 对单个函数进行立即数的去混淆处理
# 要保证应用的shellcode都是一样的,偏移才有效

# seg000:0000000000050923                 mov     rax, cs:qword_56B22
# seg000:000000000005092A                 mov     rcx, rax
# seg000:000000000005092D                 not     rcx
# seg000:0000000000050930                 mov     rdx, 636E3E08AA3F1B5h
# seg000:000000000005093A                 and     rcx, rdx
# seg000:000000000005093D                 mov     rdx, 0F9C91C1F755C0E4Ah
# seg000:0000000000050947                 and     rax, rdx
# seg000:000000000005094A                 or      rax, rcx
# seg000:000000000005094D                 mov     rbx, rax
# seg000:0000000000050950                 mov     rcx, 2161924808C44185h
# seg000:000000000005095A                 xor     rbx, rcx
# seg000:000000000005095D                 mov     rcx, 8808052500200E0Ah
# seg000:0000000000050967                 xor     rax, rcx
# seg000:000000000005096A                 mov     rcx, 0DC0A452532200E5Ah
# seg000:0000000000050974                 and     rax, rcx
# seg000:0000000000050977                 mov     rcx, 23F5BADACDDFF1A5h
# seg000:0000000000050981                 and     rbx, rcx
# seg000:0000000000050984                 or      rbx, rax
# seg000:0000000000050987                 mov     rax, 0AF5F748D48B974C4h
# seg000:0000000000050991                 xor     rbx, rax
#                                         ...
#                                         call    rbx                         ;具体的API地址


from binaryninja.enums import *
from binaryninja.plugin import *
from binaryninja.binaryview import *
from binaryninja import *
from binaryninja.function import *
from binaryninja.lowlevelil import *
from binaryninja.architecture import *

print('-'*16+'PluginLoad'+16*'-')
cf:function=current_function
cllil:LowLevelILFunction = current_llil

bv:binaryview=current_view
image_base=bv.start

# edit!!!
decrypt_table_start=0x569C2+image_base
decrypt_table_end=0x56fea+image_base

arch = Architecture['x86_64']

def deobfucation(start_index:int,end_index:int,TargetFunction:int):
   if(start_index==0 or end_index==0 or start_index >= end_index):
    print('去混淆的块地址范围判断错误')
    return

   # 获得跳转寄存器
   reg=cllil[end_index].dest
   #print('跳转寄存器 '+str(reg))
   last_index=-1
   # 从start_index到end_index搜索最后一次操作跳转寄存器的地方
   for i in range(start_index,end_index):
      if cllil[i].operation == LowLevelILOperation.LLIL_SET_REG:
         #print(cllil[i].dest.name)
         #print(reg.tokens[0])
         if cllil[i].dest==reg.src:
            last_index=i
   print('需要nop的结束地址范围 ' + hex(cllil[start_index].address)+'-'+hex(cllil[last_index].address))

   # 将start_index和last_index全部nop掉
   for i in range(start_index,last_index+1):
      bv.convert_to_nop(cllil[i].address)

   assembly_text='mov '+ reg.src.name+' , '+hex(TargetFunction)
   #print(assembly_text)
   bv.write(cllil[start_index].address,arch.assemble(assembly_text))

# 各种测试
#current_llil[23]
for bb in cllil.basic_blocks:
  deob_start_index=0  # 定位对解密表的引用
  deob_end_index=0 # 定位对ConstantValue的跳转
  deob_start_address=0
  deob_end_address=0
  # 对每一个basicblock操作
  for instruction in bb:

    if instruction.operation == LowLevelILOperation.LLIL_SET_REG and isinstance(instruction.operands[1],LowLevelILLoad) and isinstance(instruction.operands[1].src.value,ConstantPointerRegisterValue):
       if instruction.operands[1].src.value.value > decrypt_table_start and instruction.operands[1].src.value.value < decrypt_table_end:
          deob_start_index=instruction.instr_index
          deob_start_address=instruction.address
          #print(hex(instruction.address))
    # call jmp指令
    if (isinstance(instruction,LowLevelILCall) or isinstance(instruction,LowLevelILJump) ):
        # call reg 或 jmp reg
        if(isinstance(instruction.operands[0],LowLevelILReg) and isinstance(instruction.operands[0].value,ConstantPointerRegisterValue)):
           #print(instruction)
           TargetFunction=instruction.operands[0].value.value
           deob_end_index=instruction.instr_index
           deob_end_address=instruction.address
           #print(hex(TargetFunction))
           print('混淆块的起始地址 '+str(deob_start_index)+' '+hex(deob_start_address))
           print('混淆块的结束地址 '+ str(deob_end_index) +' '+hex(deob_end_address))
           
           deobfucation(deob_start_index,deob_end_index,TargetFunction)
           deob_start_address=0
           deob_end_address=0
           deob_start_index=0
           deob_end_index=0
