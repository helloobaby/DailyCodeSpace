# -*- coding: UTF-8 -*-
import os
import filetype
import pefile
import pprint

def is_pe_file(filename):
    if os.path.isfile(filename):
        kind = filetype.guess(filename)
        if kind == None:
            return False
        if kind.extension == 'exe':
            return True
    else:
        return False

string_version_info = {}
def main():
    fd = os.open('log.txt', os.O_RDWR | os.O_CREAT)
    path='C:\\Windows\\System32\\'
    files = os.listdir(path)
    for filename in files:
        if is_pe_file(path+filename):
            # 提取详细信息->文件说明
            pe = pefile.PE(path+filename)
            try:
                for fileinfo in pe.FileInfo[0]:
                    if fileinfo.Key.decode() == 'StringFileInfo':
                        for st in fileinfo.StringTable:
                            for entry in st.entries.items():
                                string_version_info[entry[0].decode()] = entry[1].decode()
                #os.write(fd, '%s : %s' %(path+filename,string_version_info['FileDescription'].encode()))
                data = '%s : %s' %(path+filename,string_version_info['FileDescription'])
                os.write(fd,data.encode())
                os.write(fd,b'\n')
            except:
                continue
    os.close(fd)
    return
if __name__ == '__main__':
    main()
