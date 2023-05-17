from binaryninja.plugin import BackgroundTaskThread,PluginCommand
from binaryninja.binaryview import BinaryView
from binaryninja.architecture import Architecture
from binaryninja.function import DisassemblyTextLine
from binaryninja.function import DisassemblyTextRenderer
import re

    # 获取指定地址的指令字符串
def get_disassembly_text(bv:BinaryView,eip:int) -> DisassemblyTextLine:
    disassembly_text = bv.get_disassembly(eip)
    disassembly_text_line = DisassemblyTextLine(disassembly_text, eip)
    return disassembly_text_line
   

# call $+5;pop reg
def handle_call_pop(bv:BinaryView,eip:int):
    value = eip+5

    # 获得reg到底是哪个寄存器,比如eax ebx等等
    insnstr = str(get_disassembly_text(bv,value))
    #print(insnstr)

    pattern = re.compile(r"pop\s+([a-zA-Z]+)")
    reg = pattern.match(insnstr).group(1)

    #print(hex(eip))
    #print(reg)
    
    insnstr = 'mov '+reg+','+hex(eip+5)
    #print(insnstr)

    # 这个相当于keystone
    arch = Architecture['x86']
    bv.write(eip,arch.assemble(insnstr))

    # 等于bv.write(addr=eip+5,data=b'\x90')
    bv.convert_to_nop(eip+5) 
    print('>> modify address at '+hex(eip))
    
def handle_push_ret(bv:BinaryView,eip:int):
    #print(hex(eip))
    insnstr = str(get_disassembly_text(bv,eip))
    pattern = re.compile(r"push\s+([a-zA-Z]+)")
    reg = pattern.match(insnstr).group(1)
    #print(reg)

    insnstr =  'jmp '+reg
    arch = Architecture['x86']
    bv.write(eip,arch.assemble(insnstr))
    print('>> modify address at '+hex(eip))


class Solver(BackgroundTaskThread):
    # bv是binaryview对象
    def __init__(self, bv:BinaryView):
        BackgroundTaskThread.__init__(self, "Resolving...", True)
        self.bv = bv

    def run(self):
        DllGetInterfaceList= self.bv.get_functions_by_name("DllGetInterface")
        if len(DllGetInterfaceList) > 1:
            print("Error : DllGetInterface is more than one")
            return
        DllGetInterface = DllGetInterfaceList[0]
        # 一般反编译器确定函数起始地址是简单的,但是很多混淆措施一加的话,结束地址就不好确定了
        start = DllGetInterface.start
        # 获得image base
        base = self.bv.start
        # 手动确定函数结尾地址
        end = base+0x4df9a

        i = start
        while i>=start and i<=end:

            #print(str(hex(i))+' : '+str(get_disassembly_text(self.bv,i)))

            first = get_disassembly_text(self.bv,i)

            # go to next instruction
            insn_len = self.bv.get_instruction_length(i)
            i+=insn_len

            next = get_disassembly_text(self.bv,i)

            if 'call' in str(first) and '$' in str(first)  and 'pop' in str(next):
                 handle_call_pop(self.bv,i-insn_len)
            elif 'push' in str(first) and 'ret' in str(next):
                 handle_push_ret(self.bv,i-insn_len)
                 
def solve(bv):
    s = Solver(bv)
    s.start()

def save_file_with_modify(bv:BinaryView):
    # 将修改保存到同路径文件    
    bv.save(bv.file.original_filename+'.back')
    print('>> save success -> '+bv.file.original_filename+'.back')

def get_function_bb(bv:BinaryView):
    base = bv.start
    bv.get_function_at()

PluginCommand.register("kill anti-disassembly", "", solve)
PluginCommand.register("save file", "", save_file_with_modify)
