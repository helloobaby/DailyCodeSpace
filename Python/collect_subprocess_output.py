import os

# 目标文件不能用相对路径
#res = os.popen('rz-bin -i ../mingw-w64-sysroot/x86_64/bin/x86_64-w64-mingw32-addr2line')

res = os.popen('rz-bin -i /root/mingw-w64-sysroot/x86_64/bin/x86_64-w64-mingw32-addr2line')

res2 = os.popen('rz-bin -l /root/rizin/build/binrz/rizin/rizin')

res3 = os.popen('rz-hash -q -a sha256 /root/rizin/build/binrz/rizin/rizin')

# 输出
print(res.read())
print('=============================')
print(res2.read())
print('=============================')
print(res3.read())
