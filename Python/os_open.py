# 如果需要文件追加，而不是截断的话，需要加上os.O_APPEND标志，如果不创建文件，需要原来文件必须存在的话，删除os.O_CREAT标志
fd = os.open('py_log.txt',os.O_RDWR|os.O_CREAT)
os.write(fd,'hello world'.encode())
os.close(fd)
