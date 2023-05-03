# copy test.py __init__.py;copy __init__.py "$env:APPDATA\Binary Ninja\plugins\test"
from binaryninja.plugin import BackgroundTaskThread,PluginCommand
from binaryninja.function import DisassemblyTextRenderer
from binaryninja.binaryview import BinaryView
from binaryninja.function import DisassemblyTextLine

def print_instruction_info(bv:BinaryView, addr):
    # Get the instruction info for the given address
    #arch = bv.arch
    #instruction_info = arch.get_instruction_info(bv.read(addr,bv.get_instruction_length(addr)),bv.get_instruction_length(addr))
    data = bv.read(addr,bv.get_instruction_length(addr))
    # 打印指令的每个字节,解析指令可以用zydis吧
    print(data.hex())


class Solver(BackgroundTaskThread):
    # bv是binaryview对象
    def __init__(self, bv:BinaryView): # 加上类型,方便IDE提示
        BackgroundTaskThread.__init__(self, "Resolving...", True)
        self.bv = bv

    def run(self):
        #renderer = DisassemblyTextRenderer()
        for f in self.bv.functions:
        # 遍历第一个函数的所有指令
        # https://api.binary.ninja/binaryninja.binaryview-module.html#binaryninja.binaryview.BinaryView.functions
        # https://api.binary.ninja/binaryninja.function.Function.html
            lowest_address = f.lowest_address
            highest_address = f.highest_address
            print('函数名字 ' + f.name + '函数范围 '+hex(lowest_address)+'-'+hex(highest_address))
                
        

        funcs = self.bv.get_functions_containing(0x1400138d4)
        i = a1 = funcs[0].lowest_address
        a2 = funcs[0].highest_address
        print(hex(a1))
        print(hex(a2))
        while i>=a1 and i<=a2:# for i in range(x)写法中无法修改i的值
            #print(self.bv.get_disassembly(i))
            disassembly_text = self.bv.get_disassembly(i)
            disassembly_text_line = DisassemblyTextLine(disassembly_text, i)
            print(disassembly_text_line)
            print_instruction_info(self.bv,i)
            len = self.bv.get_instruction_length(i)
            i+=len
        print('#'*20)
        #for block in funcs[0].basic_blocks:
            #for instruction in block.disassembly_text: # 输出整个basic block
                #print(instruction.text)


        # 遍历符号
        # https://api.binary.ninja/binaryninja.binaryview-module.html#binaryninja.binaryview.BinaryView.symbols
        # 
        for sm in self.bv.symbols:
            #print(sm)
            pass




def solve(bv):
    s = Solver(bv)
    s.start()

PluginCommand.register("Test", "this is description", solve)



