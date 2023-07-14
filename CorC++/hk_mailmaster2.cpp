// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <MinHook.h>
#include <windows.h>
#include <thread>
#include <chrono>

#include <cstdio>
#include "Sig.hpp"
#include "cef.struct.h"

wchar_t* Curl_convert_UTF8_to_wchar(const char* str_utf8) {
  wchar_t* str_w = NULL;

  if (str_utf8) {
    int str_w_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str_utf8,
                                        -1, NULL, 0);
    if (str_w_len > 0) {
      str_w = (wchar_t*)malloc(str_w_len * sizeof(wchar_t));
      if (str_w) {
        if (MultiByteToWideChar(CP_UTF8, 0, str_utf8, -1, str_w, str_w_len) ==
            0) {
          free(str_w);
          return NULL;
        }
      }
    }
  }
  return str_w;
}

inline void OutputDebug(const WCHAR* strOutputString, ...) {
  WCHAR strBuffer[4096] = {0};
  va_list vlArgs;
  va_start(vlArgs, strOutputString);
  // in stdio.h
  _vsnwprintf_s(strBuffer, ARRAYSIZE(strBuffer) - 1, ARRAYSIZE(strBuffer) - 1,
                strOutputString, vlArgs);
  va_end(vlArgs);
  OutputDebugString(strBuffer);
}

using Type_SendMailFlowWmsvr = int(__thiscall*)(char* _this);
Type_SendMailFlowWmsvr Ori_SendMailFlowWmsvr;

int __fastcall Hook_SendMailFlowWmsvr(char* _this) {
  int result = Ori_SendMailFlowWmsvr(_this);

  // 提取发件人
  // std::string::operator=((this + 0xBC), v2);
  char* sender_utf8 = (char*)*((int*)(_this + 0xBC));
  // OutputDebug(L"receiver_utf8 pointer %p\n", receiver_utf8);

  wchar_t* sender_utf16 = Curl_convert_UTF8_to_wchar(sender_utf8);
  OutputDebug(L"发件人 %ls\n", sender_utf16);

  // 提取主题
  // if ( this + 0xD4 != v6 )
  wchar_t* subject = Curl_convert_UTF8_to_wchar(_this + 0xD4);
  OutputDebug(L"发件主题 %ls\n", subject);

  // 获取发送内容1
  //[esi+4]+2C

  //int* a = *(int**)(_this + 4);
  //a = *(int**)((char*)a + 0x2C);
  //wchar_t* data1 = Curl_convert_UTF8_to_wchar((char*)a);
  //if (data1)
  //  OutputDebug(L"发件内容1 %ls\n", data1);
  //else {
  //  //a = *(int**)a;
  //  //data1 = Curl_convert_UTF8_to_wchar((char*)a);
  //  //OutputDebug(L"发件内容1 %ls\n", data1);
  //}

  // 内容2
  // [[[esi+4]]+90]

  /*int* b = *(int**)(_this + 4);
  b = *(int**)(b);
  b = *(int**)((char*)b + 0x90);

  wchar_t* data = Curl_convert_UTF8_to_wchar((char*)b);
  if (data) {
    OutputDebug(L"发件内容2 %ls\n", data);
  } else {
  }*/

  // 提取收件人
  // [[[[esi+4]]+100]]+C
  int* t = *(int**)(_this + 4);
  t = *(int**)(t);
  t = *(int**)((char*)t + 0x100);
  t = *(int**)(t);
  wchar_t* sender = Curl_convert_UTF8_to_wchar((char*)t + 0xC);
  if (!sender) {
    // OutputDebug(L"收件人 <NULL>\n");
    t = *(int**)((char*)t + 0xC);
    sender = Curl_convert_UTF8_to_wchar((char*)t);
    if (sender)
        OutputDebug(L"收件人 %ls\n", sender);
    else {
      // 调试器接管int3异常 第一次暂停
      // DebugBreak();
      OutputDebug(L"收件人 <NULL>\n");
    }
  } else
    OutputDebug(L"收件人 %ls\n", sender);

  return result;
}

MH_STATUS KStatus;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      OutputDebug(L"hk_mailmaster DLL_PROCESS_ATTACH\n");

      const int DllSize = 13564928;
      const void* SendMailFlowWmsvr = Sig::find(
          GetModuleHandle(L"mailmaster.dll"), DllSize,
          "55 8B EC 83 EC 78 A1 ?? ?? ?? ?? 33 C5 89 45 FC 53 56 57 8B F9 33 DB 89 5D 94 8B 47 04 8B 08");
      if (!SendMailFlowWmsvr) {
        OutputDebug(L"cant find SendMailFlow!\n");
        return false;
      }
      OutputDebug(L"SendMailFlowWmsvr %p\n", SendMailFlowWmsvr);

      KStatus = MH_Initialize();
      if (KStatus != MH_OK) {
        OutputDebug(L"cant init minhook\n");
        return false;
      }

      HMODULE HMailMaster = LoadLibrary(L"mailmaster.dll");

      KStatus = MH_CreateHook((LPVOID)SendMailFlowWmsvr, Hook_SendMailFlowWmsvr,
                              (LPVOID*)&Ori_SendMailFlowWmsvr);


      MH_EnableHook((LPVOID)SendMailFlowWmsvr);

      DisableThreadLibraryCalls(hModule);
      break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
