import os

# 列出当前目录下所有的文件
files = os.listdir('.')
for filename in files:
    portion = os.path.splitext(filename)
    print(portion)
    if portion[1] == '.txt':
        os.rename(filename,portion[0])
