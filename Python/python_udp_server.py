import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
# �ͻ���д��
#len = s.sendto(b'hello',('47.120.3.243',6666))
#print(len)
# �����
s.bind(('127.0.0.1',6666))
while(True):
    data,addr = s.recvfrom(4096)
    print('�¿ͻ��� : '+addr[0]+':'+str(addr[1])+'  ���� : '+data.decode('utf-8'))
    #print(data)

