// https://github.com/helloobaby/DailyCodeSpace/blob/master/CorC%2B%2B/openssl.cpp
// windows vs2019上编译
// 不验证证书
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cassert>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

const char* server_ip = "110.242.68.66";
#define port 443

int main() {
	WSADATA wsaData;
	ERR_load_crypto_strings();
	if (WSAStartup(MAKEWORD(2, 1), &wsaData))
	{
	
		return 1;
	}
	SSL_CTX* ctx;
	SSL* ssl;
	/* SSL 库初始化 */
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_method());
	assert(ctx);

	// 验证服务器证书
	//SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
	// 不验证服务器证书,但是必须有证书
	SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL); 

	ssl = SSL_new(ctx);

	SOCKET sockfd;
	// 三次握手
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);                      /* 服务器监听端口 */
	serverAddr.sin_addr.S_un.S_addr = inet_addr(server_ip);     /* 服务器地址 */

	int len = sizeof(serverAddr);
	connect(sockfd, (SOCKADDR*)&serverAddr, len);


	// https://www.openssl.org/docs/manmaster/man3/SSL_set_fd.html
	int ret=SSL_set_fd(ssl, sockfd);
	if (ret != 1) {
		assert(0);
	}
	int error = SSL_get_error(ssl, ret);

	ret=SSL_connect(ssl);
	if (ret < 0) {
		error = SSL_get_error(ssl, ret);
		int ssl_error = SSL_get_verify_result(ssl);
		assert(0);
	}

	SSL_write(ssl, "123", 3);
	SSL_write(ssl, "123", 3);
	SSL_write(ssl, "123", 3);
	SSL_write(ssl, "123", 3);
	SSL_write(ssl, "123", 3);
	SSL_write(ssl, "123", 3);

	//SSL_accept(ssl);

	//ret = SSL_do_handshake(ssl);

	//error = SSL_get_error(ssl, ret);

	return 0;
}
