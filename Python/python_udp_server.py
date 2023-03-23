import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
# 客户端写法
#len = s.sendto(b'hello',('47.120.3.243',6666))
#print(len)
# 服务端
s.bind(('127.0.0.1',6666))
while(True):
    data,addr = s.recvfrom(4096)
    print('新客户端 : '+addr[0]+':'+str(addr[1])+'  数据 : '+data.decode('utf-8'))
    #print(data)

