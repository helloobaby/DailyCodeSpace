#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cassert>

int main() {
  SSL_CTX *ctx;
  SSL *ssl;
  /* SSL 库初始化 */
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  ctx = SSL_CTX_new(TLS_client_method());
  assert(ctx);

  // 验证服务器证书
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
  // 不验证服务器证书,但是必须有证书
  //SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL); 

  return 0;
}

