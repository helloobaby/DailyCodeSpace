// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Sig.hpp"
#include <windows.h>
#include <cstdio>
#include <MinHook.h>
#include <curl/curl.h>
__declspec(dllexport) void ijtdummy(
) { 
    //for inject
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

//https://github.com/curl/curl/blob/master/lib/setopt.c#L190
CURLcode Hook_Curl_vsetopt(struct Curl_easy* data, CURLoption option,
                           va_list param);
using Type_Curl_vsetopt =decltype(&Hook_Curl_vsetopt);
Type_Curl_vsetopt Ori_Curl_vsetopt;

MH_STATUS KStatus;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      OutputDebug(L"[log]DLL_PROCESS_ATTACH\n");

      const int DllSize = 52152344;
      const void* Curl_vsetopt =
          Sig::find(GetModuleHandle(NULL), DllSize,
                    "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 "
                    "20 41 56 48 83 EC 40 33 ED 49 8B F0");
      if (!Curl_vsetopt) {
        OutputDebug(L"cant find curl_easy_setopt!\n");
        return false;
      } else {
        // PathOfExile.exe+0x2125090
        OutputDebug(L"[log]curl_easy_setopt %p\n", Curl_vsetopt);
      }

      KStatus = MH_Initialize();
      if (KStatus != MH_OK) {
        OutputDebug(L"[log]cant init minhook\n");
        return false;
      }

      KStatus = MH_CreateHook((LPVOID)Curl_vsetopt, Hook_Curl_vsetopt,
                              (LPVOID*)&Ori_Curl_vsetopt);

      MH_EnableHook((LPVOID)Curl_vsetopt);

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

CURLcode Hook_Curl_vsetopt(struct Curl_easy* data, CURLoption option,
    va_list param) {
  CURLcode Res = Ori_Curl_vsetopt(data, option, param);
  OutputDebug(L"[log]Hook_Curl_vsetopt\n");
  return Res;
}
