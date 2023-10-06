// 校验服务器证书
// https://blog.csdn.net/weichi7549/article/details/107577423
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <cassert>
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

const char* server_ip = "43.241.16.222";
#define port 56158

int main() {

    getchar();

    WSADATA wsaData;
    ERR_load_crypto_strings();
    if (WSAStartup(MAKEWORD(2, 1), &wsaData)) {
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

    ssl = SSL_new(ctx);

    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

    SOCKET sockfd;
    // 三次握手
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); /* 服务器监听端口 */
    serverAddr.sin_addr.S_un.S_addr = inet_addr(server_ip); /* 服务器地址 */

    int len = sizeof(serverAddr);
    connect(sockfd, (SOCKADDR*)&serverAddr, len);

    // https://www.openssl.org/docs/manmaster/man3/SSL_set_fd.html
    int ret = SSL_set_fd(ssl, sockfd);
    if (ret != 1) {
        assert(0);
    }
    int error = SSL_get_error(ssl, ret);

    ret = SSL_connect(ssl);
    if (ret < 0) {

        error = SSL_get_error(ssl, ret);
        int ssl_error = SSL_get_verify_result(ssl);
        assert(0);
    }

    X509* server_cert = SSL_get_peer_certificate(ssl);
    if (server_cert == nullptr) {
        // 未能获取证书，处理错误
        // 这里需要添加错误处理代码
        assert(0);
    }


    auto* subject = X509_get_subject_name(server_cert);
    auto* issuer = X509_get_issuer_name(server_cert);
    // 输出证书主题和颁发者信息
    printf("证书主题: %s\n", X509_NAME_oneline(subject, nullptr, 0));
    printf("证书颁发者: %s\n", X509_NAME_oneline(issuer, nullptr, 0));




    return 0;
}
