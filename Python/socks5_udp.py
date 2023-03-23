import os
import socket
import socketserver
import struct

class MyTCPHandler(socketserver.BaseRequestHandler):
    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024)
        version, nmethods,methods = struct.unpack("!BBB", self.data)
        if version != 5 and nmethods != 1 and methods != 0 :
            print("-- 目前只支持socks5版本，一种验证方式，无验证需求")
            exit(0)
        temp_data = b'\x05\x00' # 告诉客户端验证方式
        self.request.sendall(temp_data)

        self.request.recv(1024)



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