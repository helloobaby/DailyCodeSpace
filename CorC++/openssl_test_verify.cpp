// 校验服务器证书
// https://blog.csdn.net/weichi7549/article/details/107577423
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <cassert>
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

const char* server_ip = "110.242.68.66";
#define port 443

int main() {
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

  // 验证服务器证书
  // SSL_VERIFY_FAIL_IF_NO_PEER_CERT 这个好像是双向认证
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
  int err;

  //err=SSL_CTX_use_certificate_file(ctx, "root.pem.cer", SSL_FILETYPE_PEM);
  // err=SSL_CTX_use_PrivateKey_file(ctx, "root.pem.key", SSL_FILETYPE_PEM);

  // SSL_CTX_load_verify_file(ctx, pem);

  // err = SSL_CTX_check_private_key(ctx);

  
  //err=SSL_CTX_set_default_verify_paths(ctx);

  //X509_STORE* store = SSL_CTX_get_cert_store(ctx);

  const char* pem = R"(-----BEGIN CERTIFICATE-----
MIIDXzCCAkegAwIBAgILBAAAAAABIVhTCKIwDQYJKoZIhvcNAQELBQAwTDEgMB4G
A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjMxEzARBgNVBAoTCkdsb2JhbFNp
Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDkwMzE4MTAwMDAwWhcNMjkwMzE4
MTAwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMzETMBEG
A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI
hvcNAQEBBQADggEPADCCAQoCggEBAMwldpB5BngiFvXAg7aEyiie/QV2EcWtiHL8
RgJDx7KKnQRfJMsuS+FggkbhUqsMgUdwbN1k0ev1LKMPgj0MK66X17YUhhB5uzsT
gHeMCOFJ0mpiLx9e+pZo34knlTifBtc+ycsmWQ1z3rDI6SYOgxXG71uL0gRgykmm
KPZpO/bLyCiR5Z2KYVc3rHQU3HTgOu5yLy6c+9C7v/U9AOEGM+iCK65TpjoWc4zd
QQ4gOsC0p6Hpsk+QLjJg6VfLuQSSaGjlOCZgdbKfd/+RFO+uIEn8rUAVSNECMWEZ
XriX7613t2Saer9fwRPvm2L7DWzgVGkWqQPabumDk3F2xmmFghcCAwEAAaNCMEAw
DgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFI/wS3+o
LkUkrk1Q+mOai97i3Ru8MA0GCSqGSIb3DQEBCwUAA4IBAQBLQNvAUKr+yAzv95ZU
RUm7lgAJQayzE4aGKAczymvmdLm6AC2upArT9fHxD4q/c2dKg8dEe3jgr25sbwMp
jjM5RcOO5LlXbKr8EpbsU8Yt5CRsuZRj+9xTaGdWPoO4zzUhw8lo/s7awlOqzJCK
6fBdRoyV3XpYKBovHd7NADdBj+1EbddTKJd+82cEHhXXipa0095MJ6RMG3NzdvQX
mcIfeg7jLQitChws/zyrVQ4PkX4268NXSb7hLi18YIvDQVETI53O9zJrlAGomecs
Mx86OyXShkDOOyyGeMlhLxS67ttVb9+E7gUJTb0o2HLO02JQZR7rkpeDMdmztcpH
WD9f
-----END CERTIFICATE-----
)";

  err=SSL_CTX_load_verify_locations(ctx, "root.pem.cer", NULL);
  //SSL_CTX_load_verify_locations(ctx, pem, NULL);


  ssl = SSL_new(ctx);

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

  SSL_write(ssl, "123", 3);
  SSL_write(ssl, "123", 3);
  SSL_write(ssl, "123", 3);
  SSL_write(ssl, "123", 3);
  SSL_write(ssl, "123", 3);
  SSL_write(ssl, "123", 3);

  // SSL_accept(ssl);

  // ret = SSL_do_handshake(ssl);

  // error = SSL_get_error(ssl, ret);

  return 0;
}
