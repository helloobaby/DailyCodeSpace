
from qiling import Qiling
from qiling.const import QL_ARCH, QL_OS, QL_VERBOSE
from unicorn.x86_const import *
from colorama import Fore,Back,Style,init


file_path=r'rootfs/x86_windows/26d0000.shc'

init(wrap=True, autoreset=True)
f=open(file_path,'rb')
buf = f.read()
ql = Qiling(code=buf, rootfs=r"rootfs/x86_windows",archtype=QL_ARCH.X86,ostype=QL_OS.WINDOWS,verbose=QL_VERBOSE.DEFAULT)

ql.run()
