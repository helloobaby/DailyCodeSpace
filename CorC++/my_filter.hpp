//NetFilter SDK demo
//PassThrough.cpp 包含此头文件

#include "nfapi.h"
#include <string>
#include <ranges>
#include <memory>
#include <format>
#include <spdlog/sinks/basic_file_sink.h>

using namespace nfapi;
using namespace std;  // 不加影响编译器静态代码分析

// 初始化日志
std::shared_ptr<spdlog::logger> kLogger;
void InitLogger() {
  kLogger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
}
//

// 打印包的内容
// 如果要实时写入文件的话,就必须是同步的spdlog
// 但是会造成线程阻塞
void PrintPacket(const unsigned char* buf, int len) {
  for (int i = 0; i < len; i++) {
    printf("0x%x ", buf[i]);
  }
  puts("\n");
}


void My_udpSend(ENDPOINT_ID id, const char* remoteAddress,
                unsigned char* buf, int len, PNF_UDP_OPTIONS options) {

  auto range = string_view(remoteAddress) | ranges::views::split(':');
  auto sub_range = ++range.begin();
  string_view port = string_view(&*(*sub_range).begin(),ranges::distance(*sub_range));

  //tcpudp2.1.1.exe
  #if 0
  if (port == "6666") {
    PrintPacket(buf,len);
  }
  #endif

  // 每个部署的服务器端口不一定一样
  // 饥了个荒 4档海钓 10999
  if (port == "10999") {
      // 喊话包
    if (len > 22 && (buf[20] == 0x2a) && (buf[21] == 0xca) && (buf[22] == 0x80)) {
        //puts("喊话包:");
        //PrintPacket((unsigned char*)buf, len);

        string s = std::format("喊话包:\n");
        


        // 改包测试,第一个字符改成1
        buf[25] = 0x31;
    } else if (len > 22 && (buf[20] == 0x54) && (buf[21] == 0x4a) && (buf[22] == 0x80)) {
      //puts("钓鱼包:");
        //PrintPacket((unsigned char*)buf, len);
    }



  }


}