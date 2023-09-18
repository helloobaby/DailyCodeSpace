#
#Backspace



from binaryninja import *


# llil.operation == <LowLevelILOperation.LLIL_IF: 59>

# if (eax != 0x1ffdbaed) then 16 @ 0x1400124d5 else 25 @ 0x1400124e5
# llil.condition == binaryninja.lowlevelil.LowLevelILCmpNe
# if (eax == 0x46bab93) then 20 @ 0x1400124fa else 24 @ 0x1400124e3
# llil.condition == binaryninja.lowlevelil.LowLevelILCmpE


state_action={}
arch = Architecture['x86']
patch_task={}
swVar='eax'

# 模式匹配特征块
def is_dispatch_bb(bb:LowLevelILBasicBlock):
    if bb.length == 1 and bb[0].operation == LowLevelILOperation.LLIL_IF and isinstance(bb[0].operands[0].left,LowLevelILReg):
        return True
        
def get_state_action(bb:LowLevelILBasicBlock):


    # cmp     eax, 0xdf71dc86
    # je      0x1400124f6
    # lowlevelil只有一条指令
    assert(len(bb)==1)
    
    print('识别的分发块'+ str(bb[0]))
    #print(type(bb[0]))
    
    op1=bb[0].operands[0].operands[1].value
    state=0
    action=0
    
    # 分je\jne情况枚举
    if isinstance(bb[0].condition,LowLevelILCmpNe):
        if isinstance(op1,ConstantRegisterValue): # if (eax == 0xdf71dc86)
            state=op1.value
            action=current_llil[bb[0].operands[2]].address
    if isinstance(bb[0].condition,LowLevelILCmpE):
        if isinstance(op1,ConstantRegisterValue):
            state=op1.value
            action=current_llil[bb[0].operands[1]].address

    if state and action:
        print('state %#x-> action %#x' %(state,action))
        state_action[state]=action


# 解析指令,收集所有更改状态的指令地址
# mov eax,<constant value>
def change_state(text_token_list:list):
    if (len(text_token_list) < 4 ):
        return None
    #print(text_token_list)
    if str(text_token_list[0]) == 'mov' and str(text_token_list[2]) == swVar and text_token_list[4].value !=0:
        # 返回state
        return text_token_list[4].value
    
    return None


# 获得这条指令在这个函数对应的basicblock
def get_addr_in_basicblock(addr:int):
    for bb in current_function.basic_blocks:
        for text in bb.disassembly_text:
            if text.address==addr:
                return bb
        
    print('error : %#x not in any block ? ' % addr)
    return None
    
# 这条指令在这个basicblock里patch安全吗
def is_safely_patched(addr:int,bb:BasicBlock):
    # 理论上来说这条指令后面应该要没有有效的指令
    # 无效指令包括(所有的jcc nop)
    
    for insn_text in bb.disassembly_text:
        if insn_text.address > addr:
            #print(hex(insn_text.address))
            if 'nop' != str(insn_text.tokens[0]) and 'jmp' != str(insn_text.tokens[0]): # 这条指令既不是nop 也不是jcc ,不安全
                return False
            
    return True
    

# 首先正确提取分发块和真实块
for bb in current_llil.basic_blocks:
    if(is_dispatch_bb(bb)):
        get_state_action(bb)
print(32*'*')
        

for bb in current_function.basic_blocks:
    
    # 统计这个basicblock的指令数，什么len length全是指令字节数
    instruction_count=len(bb.disassembly_text)
    
    
    for i in range(0,instruction_count-1):
        
        if change_state(bb[i][0]) != None:
            address=bb.disassembly_text[i].address
            print('识别到的更改状态的指令地址 ' + hex(address))
            print(get_addr_in_basicblock(address))
            if(is_safely_patched(address,get_addr_in_basicblock(address))):
                print('安全patch')
            else:
                print('Patch不了')
                # 获得状态
                jmp_dest_state=change_state(bb[i][0])
                # 获得状态对应的真实代码块
                jmp_dest=state_action[jmp_dest_state]
                
                insnstr =  'jmp '+ hex(jmp_dest)
                print('patch后的指令字符串' + insnstr)
                
                # 最后再patchaddr in patch_task:
                patch_task[address]=insnstr
            pass

for address in patch_task:
    bv.write(address,arch.assemble(patch_task[address],addr=address))
