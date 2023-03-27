//NetFilter SDK demo
//PassThrough.cpp ������ͷ�ļ�

#include "nfapi.h"
#include <string>
#include <ranges>
#include <memory>
#include <format>
#include <spdlog/sinks/basic_file_sink.h>

using namespace nfapi;
using namespace std;  // ����Ӱ���������̬�������

// ��ʼ����־
std::shared_ptr<spdlog::logger> kLogger;
void InitLogger() {
  kLogger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
}
//

// ��ӡ��������
// ���Ҫʵʱд���ļ��Ļ�,�ͱ�����ͬ����spdlog
// ���ǻ�����߳�����
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

  // ÿ������ķ������˿ڲ�һ��һ��
  // ���˸��� 4������ 10999
  if (port == "10999") {
      // ������
    if (len > 22 && (buf[20] == 0x2a) && (buf[21] == 0xca) && (buf[22] == 0x80)) {
        //puts("������:");
        //PrintPacket((unsigned char*)buf, len);

        string s = std::format("������:\n");
        


        // �İ�����,��һ���ַ��ĳ�1
        buf[25] = 0x31;
    } else if (len > 22 && (buf[20] == 0x54) && (buf[21] == 0x4a) && (buf[22] == 0x80)) {
      //puts("�����:");
        //PrintPacket((unsigned char*)buf, len);
    }



  }


}