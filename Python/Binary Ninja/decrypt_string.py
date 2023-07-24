# 先执行
# \BinaryNinja_v3.1.3469_Windows\BinaryNinja\scripts\install_api.py
# 这样vscode就能识别到binaryninja库了,支持高亮和代码补全

# https://docs.binary.ninja/dev/bnil-llil.html

from binaryninja.plugin import BackgroundTaskThread,PluginCommand
from binaryninja.binaryview import BinaryView
from binaryninja.architecture import Architecture
from binaryninja.function import DisassemblyTextLine
from binaryninja.function import DisassemblyTextRenderer
from binaryninja.enums import HighLevelILOperation,LowLevelILOperation
from binaryninja.highlevelil import HighLevelILInstruction
from binaryninja.lowlevelil import LowLevelILInstruction,LowLevelILConstPtr


# 0x18000172a <class 'binaryninja.lowlevelil.LowLevelILConstPtr'>            call    sub_180002f50  
# 0x18000176f <class 'binaryninja.lowlevelil.LowLevelILLoad'>                call    qword [rel RegOpenKeyExA]

def do_nothing(bv:BinaryView):
    # 0x180001340是解密字符串函数的地址
    target_function = bv.get_function_at(0x180001340)
    for caller_function in set(target_function.callers):
        # 调用过目标函数的函数
        print(caller_function)
        for bb in caller_function.low_level_il:
            for instr in bb:
                if instr.operation == LowLevelILOperation.LLIL_CALL:
                    if isinstance(instr.dest,LowLevelILConstPtr):
                        if instr.dest.constant == target_function.start:  # call target_function
                            #print(hex(instr.address,instr.get_reg_value('R9')))
                            len_str = hex(instr.get_reg_value('r9').value)
                            data_ptr = hex(instr.get_reg_value('r8').value)
                            print(hex(instr.address),len_str,data_ptr)
                            

                        


PluginCommand.register("Useless Plugin", "Basically does nothing", do_nothing)
