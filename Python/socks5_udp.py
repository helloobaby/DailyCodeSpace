#https://docs.python.org/3/library/socketserver.html
#https://www.ddhigh.com/2019/08/24/socks5-protocol.html
#https://docs.python.org/3/library/struct.html
import os
import select
import socket
import socketserver
import struct
import threading

def change_loop(remote_socket,client_socket):
    while(True):
        r,w,e = select.select([remote_socket,client_socket],[],[])
        if remote_socket in r:
            data = remote_socket.recv(4096)
            if data== b'':
                return
            print('服务器返回:')
            print(data)

        if client_socket in r:
            data = client_socket.recv(4096)
            remote_socket.sendall(data)
            if data== b'':
                return
            print('客户端发来请求:')
            print(data)



class MyTCPHandler(socketserver.BaseRequestHandler):
    def handle(self):
        # self.request is the TCP socket connected to the client
        print(" new client")
        self.data = self.request.recv(1024)
        version, nmethods,methods = struct.unpack("!BBB", self.data)
        if version != 5 and nmethods != 1 and methods != 0 :
            print("-- 目前只支持socks5版本，一种验证方式，无验证需求")
            return
        temp_data = b'\x05\x00' # 告诉客户端验证方式
        # 此时我感觉协议握手就完成了
        self.request.sendall(temp_data)

        #while(True):
        self.data = self.request.recv(1024)
        version,cmd,rsv,addr_type = struct.unpack_from("!BBBB",self.data,0)
        # 连接指定服务器(域名)
        if version == 5 and cmd == 1 and addr_type == 3:
            domain_len = struct.unpack_from('!B',self.data,4)
            #print(domain_len[0])
            domain = struct.unpack_from('!'+str(domain_len[0])+'s',self.data,5)
            #print(domain[0])
            port = struct.unpack_from('!h',self.data,5+domain_len[0])
            #print(port[0])
            self.request_remote = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            self.request_remote.connect((domain[0],port[0]))
            bind_address = self.request_remote.getsockname()
            # 4字节序列转整数
            addr = struct.unpack("!I", socket.inet_aton(bind_address[0]))[0]
            reply = struct.pack("!BBBIH",5,0,0,addr,bind_address[1])
            self.request.sendall(reply)
            # 消息转发
            change_loop(self.request_remote,self.request)
            pass
        # 连接指定服务器(ipv4)
        elif version == 5 and cmd == 1 and addr_type == 1:
            ip_int = struct.unpack_from('!I',self.data,4)
            ip_string = socket.inet_ntoa(ip_int[0].to_bytes(4,byteorder='big'))
            port = struct.unpack_from('!h',self.data,8)
            print('有客户端想要连接指定ip : ')
            print(ip_string)
            self.request_remote = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.request_remote.connect((ip_string, port[0]))
            bind_address = self.request_remote.getsockname()
            # 4字节序列转整数
            addr = struct.unpack("!I", socket.inet_aton(bind_address[0]))[0]
            reply = struct.pack("!BBBBIH", 5, 0, 0,1 ,addr, bind_address[1])
            self.request.sendall(reply)
            change_loop(self.request_remote,self.request)
            pass
        elif version == 5 and cmd == 3 and addr_type == 1:
            print('udp')


class MyUDPHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        print("{} wrote:".format(self.client_address[0]))
        print(data)
        socket.sendto(data.upper(), self.client_address)

if __name__ == "__main__":
    HOST, PORT = "localhost", 6666
    with socketserver.TCPServer((HOST, PORT), MyTCPHandler) as server:
        server.serve_forever()