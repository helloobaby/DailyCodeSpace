# 遍历当前文件夹所有lib文件,并且打印出lib名
import os
files = os.listdir('.')
for filename in files:
    if filename.endswith('.lib'):
        print(filename+';',end='')

