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

  // 提取收件人
  char* receiver_utf8 = (char*)*((int*)(_this + 0xBC));
  //OutputDebug(L"receiver_utf8 pointer %p\n", receiver_utf8);

  wchar_t* receiver_utf16 = Curl_convert_UTF8_to_wchar(receiver_utf8);
  OutputDebug(L"发件人 %ls\n", receiver_utf16);

  wchar_t* subject = Curl_convert_UTF8_to_wchar(_this + 0xD4);
  OutputDebug(L"发件主题 %ls\n", subject);

  char* t = (char*)(*(int*)(_this + 4));
  t = (char*)*((int*)(t + 0x2C));
  t = (char*)*(int*)t;

  wchar_t* data = Curl_convert_UTF8_to_wchar(t); 
  OutputDebug(L"发件内容 %ls\n", data);

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
