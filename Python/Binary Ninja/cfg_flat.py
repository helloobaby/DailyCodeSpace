#
#Backspace

#
# binaryninja Snippets plugin to run this script
# 比较通用的解决控制流平台化混淆脚本

from binaryninja import *
import sys

# llil.operation == <LowLevelILOperation.LLIL_IF: 59>

# if (eax != 0x1ffdbaed) then 16 @ 0x1400124d5 else 25 @ 0x1400124e5
# llil.condition == binaryninja.lowlevelil.LowLevelILCmpNe
# if (eax == 0x46bab93) then 20 @ 0x1400124fa else 24 @ 0x1400124e3
# llil.condition == binaryninja.lowlevelil.LowLevelILCmpE


state_action = {}
arch = Architecture['x86']
patch_task = {}

# cmp eax,<constant value> 或者是 cmp ecx,<constant value>
swVar = 'eax'
#swVar = 'ecx'

# llil上模式匹配特征块,一般是通用的
def is_dispatch_bb(bb: LowLevelILBasicBlock):
    # example分发块
    # if (eax != 0xe) then 159 @ 0x1400b4076 else 160 @ 0x1400b4069
    if bb.length == 1 and bb[0].operation == LowLevelILOperation.LLIL_IF and isinstance(bb[0].operands[0].left,
                                                                                        LowLevelILReg) and \
            bb[0].operands[0].left.src.name == swVar:
        print('识别的分发块起始地址llil  -> ' + hex(current_llil[bb.start].address))
        return True


def get_state_action(bb: LowLevelILBasicBlock):
    op1 = bb[0].operands[0].operands[1].value
    state = 0
    action = 0

    # 分je\jne情况枚举
    if isinstance(bb[0].condition, LowLevelILCmpNe):  #
        if isinstance(op1, ConstantRegisterValue):
            state = op1.value
            action = current_llil[bb[0].operands[2]].address

    if isinstance(bb[0].condition, LowLevelILCmpE):
        if isinstance(op1, ConstantRegisterValue):
            state = op1.value
            action = current_llil[bb[0].operands[1]].address

    print('Id(State) %#x-> Block(Action) %#x' % (state, action))
    state_action[state] = action


# 解析指令,收集所有更改状态的指令地址
# 根据指令关键字解析 搜索以下模式mov     eax, <const_value>
def change_state(text_token_list: list) -> int:
    if (len(text_token_list) < 4):
        return None
    # print(text_token_list)
    if str(text_token_list[0]) == 'mov' and str(text_token_list[2]) == swVar and text_token_list[
        4].type == InstructionTextTokenType.IntegerToken:
        # 有可能是正常的给eax赋值,也有可能之前没收集到这个state(代码不完善)
        state = text_token_list[4].value
        if state not in state_action:
            return None
        # 返回state
        return state
    return None


# 获得这条指令在这个函数对应的basicblock
def get_addr_in_basicblock(addr: int) -> basicblock:
    for bb in current_function.basic_blocks:
        for text in bb.disassembly_text:
            if text.address == addr:
                return bb

    print('Error : %#x not in any block ? ' % addr)
    sys.exit(-1)
    return None

def get_addr_in_llbasicblock(addr:int) -> LowLevelILBasicBlock:
    for i in range(len(current_llil)):
        #print(hex(current_llil[i].address))
        if current_llil[i].address == addr:
            return current_llil[i].il_basic_block
    # lowlevel 一个指令可能对应多个低级汇编指令
    # 不一定是一对一的
    return None




# addr:应该是mov <reg>,<constant value>的指令的具体地址
# bb: addr指令所在的basicblock
# 返回需要被patch成jmp的地址
def is_safely_patched(addr: int):
    bb = get_addr_in_basicblock(addr)
    llbb = get_addr_in_llbasicblock(addr)
    llil = llbb[-1]

    # 这个basicblock最后一条指令执行的时候swVar必须是常量
    try:
        llil.get_possible_reg_values(swVar).value
    except:
        return None


    # 如果basicblock最后有一个>=5字节的nop,我可以直接在这里patch
    if bb[-1][1] >= 5 and str(bb[-1][0][0]) == 'nop':
        return bb.disassembly_text[-1].address

    # 最不济的情况下,把mov 这条指令patch了
    # 需要校验后面有没有有效指令
    for insn_text in bb.disassembly_text:
        if insn_text.address > addr:
            if 'nop' != str(insn_text.tokens[0]) and 'jmp' != str(insn_text.tokens[0]): # 这条指令既不是nop 也不是jcc ,不安全
                return None

    return addr


# main

# 首先正确提取分发块和真实块
for bb in current_llil.basic_blocks:
    if (is_dispatch_bb(bb)):
        get_state_action(bb)

# 调试
#sys.exit(0)


for bb in current_function.basic_blocks:

    # 统计这个basicblock的指令数，什么len length全是指令字节数
    instruction_count = len(bb.disassembly_text)

    for i in range(0, instruction_count):
        address = bb.disassembly_text[i].address

        # 主要是有Does not return这种东西
        # instruction_count为2,实际索引只能为0,1直接越界
        try:
            state = change_state(bb[i][0])
        except:
            continue
        if state != None:
            print('识别到的更改状态的指令地址 ' + hex(address))

            # 调试
            # continue

            patched_address = is_safely_patched(address)
            if (patched_address != None):
                print('安全patch %#x' %(patched_address))

                # 调试
                #continue

                # 获得状态
                jmp_dest_state = state

                # 获得状态对应的真实代码块
                jmp_dest = state_action[jmp_dest_state]

                insnstr = 'jmp ' + hex(jmp_dest)

                # 最后再patchaddr in patch_task:
                patch_task[patched_address] = insnstr

            else:
                print('Patch不了')

for address in patch_task:
    bv.write(address, arch.assemble(patch_task[address], addr=address))

