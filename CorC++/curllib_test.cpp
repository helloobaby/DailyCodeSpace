#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <intrin.h>
#include <stdint.h>
#include <curl/curl.h>

#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")

#include <windows.h>
int main() {
  getchar();
  const char *netlink = "https://static.getiot.tech/flag-of-china.png";
  curl_global_init(CURL_GLOBAL_ALL);  
  CURL *curl = curl_easy_init();    
  curl_easy_setopt(curl, CURLOPT_URL, netlink);

  // 关掉证书校验之后,HttpAnalyzer就可以抓到https包了
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

  curl_easy_perform(curl);
  
  getchar();

  return 2;
}
