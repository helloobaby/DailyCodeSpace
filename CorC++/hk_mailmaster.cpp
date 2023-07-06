// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <windows.h>
#include <cstdio>
#include <MinHook.h>

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

MH_STATUS KStatus;
HMODULE handle;
FARPROC p_cef_browser_host_create_browser;

int hook_cef_browser_host_create_browser(int* p1, int* p2, int* p3, int* p4,
                                         int* p5);
using type_cef_browser_host_create_browser = decltype(&hook_cef_browser_host_create_browser);
type_cef_browser_host_create_browser ori_cef_browser_host_create_browser;

int hook_cef_browser_host_create_browser(int* p1, int* p2, int* p3, int* p4,
                                         int* p5) {

    int* client = p2;
    //g_cef_get_keyboard_handler = client->get_keyboard_handler
    OutputDebug(L"client at %p\n", client);






  return ori_cef_browser_host_create_browser(p1, p2, p3, p4, p5);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      OutputDebug(L"Hello Hello\n");
      KStatus = MH_Initialize();
      if (KStatus != MH_OK) {
        OutputDebug(L"cant init minhook\n");
        return false;
      }

      handle = GetModuleHandle(L"libcef.dll");
      if (handle == NULL) {
        OutputDebug(L"cant find libcef.dll\n");
        return false;  //卸载
      }
      p_cef_browser_host_create_browser =
          GetProcAddress(handle, "cef_browser_host_create_browser");

      if (!p_cef_browser_host_create_browser) {
        OutputDebug(L"cant find cef_browser_host_create_browser \n");
        return false;
      }

      KStatus = MH_CreateHook(p_cef_browser_host_create_browser,
                              hook_cef_browser_host_create_browser,
                              (LPVOID*)&ori_cef_browser_host_create_browser);
      MH_EnableHook(p_cef_browser_host_create_browser);
      DisableThreadLibraryCalls(hModule);
      break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

