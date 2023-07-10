// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <MinHook.h>
#include <windows.h>
#include <thread>
#include <chrono>

#include <cstdio>
#include "Sig.hpp"
#include "cef.struct.h"

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

int hook_cef_browser_host_create_browser(int* p1, int* p2, int* p3, int* p4,
                                         int* p5);
using type_cef_browser_host_create_browser =
    decltype(&hook_cef_browser_host_create_browser);
type_cef_browser_host_create_browser ori_cef_browser_host_create_browser;

int CEF_CALLBACK hook_get_keyboard_handler(void* p1);
using type_get_keyboard_handler = decltype(&hook_get_keyboard_handler);
int CEF_CALLBACK hook_get_context_menu_handler(void* p1);

int CEF_CALLBACK hook_get_load_handler(void* p1);

int CEF_CALLBACK hook_get_render_handler(void* p1);

  int(CEF_CALLBACK hook_get_screen_info)(void* self, void* browser,
                                       void* screen_info);
using type_get_screen_info = decltype(&hook_get_screen_info);

int CEF_CALLBACK sighook_get_screen_info(int* a1, int a2, int a3, int a4);
using type_sighook_get_screen_info = decltype(&sighook_get_screen_info);
type_sighook_get_screen_info ori_sighook_get_screen_info;

 using type_show_dev_tools = void(CEF_CALLBACK*)(
    void* self,
    const struct _cef_window_info_t* windowInfo, struct _cef_client_t* client,
    const struct _cef_browser_settings_t* settings,
    const cef_point_t* inspect_element_at);

MH_STATUS KStatus;
HMODULE handle;
FARPROC p_cef_browser_host_create_browser;
type_get_keyboard_handler p_get_keyboard_handler;
type_get_keyboard_handler p_get_context_menu_handler;
type_get_keyboard_handler p_get_load_handler;
type_get_keyboard_handler p_get_render_handler;
type_get_screen_info ori_p_get_screen_info;

void SetAsPopup(cef_window_info_t* window_info) {
  window_info->style =
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
  window_info->parent_window = NULL;
  window_info->x = CW_USEDEFAULT;
  window_info->y = CW_USEDEFAULT;
  window_info->width = CW_USEDEFAULT;
  window_info->height = CW_USEDEFAULT;
}

int hook_cef_browser_host_create_browser(int* p1, int* p2, int* p3, int* p4,
                                         int* p5) {
  int* client = p2;
  // g_cef_get_keyboard_handler = client->get_keyboard_handler
  OutputDebug(L"client at %p\n", client);

  static bool once = 0;
  //if (!once) {
  if (1){
    // 记录原来的回调地址
    p_get_keyboard_handler = (type_get_keyboard_handler)client[13];
    p_get_context_menu_handler = (type_get_keyboard_handler)client[1];
    p_get_load_handler = (type_get_keyboard_handler)client[15];
    p_get_render_handler = (type_get_keyboard_handler)client[17];
    // hook
    //client[13] = (int)&hook_get_keyboard_handler;
    //client[1] = (int)&hook_get_context_menu_handler;
    //client[15] = (int)&hook_get_load_handler;
    //client[17] = (int)&hook_get_render_handler;

    once = !once;
  }
  return ori_cef_browser_host_create_browser(p1, p2, p3, p4, p5);
}


int CEF_CALLBACK hook_get_keyboard_handler(void* p1) {
  // _cef_keyboard_handler_t
  int* keyboard_handler = (int*)p_get_keyboard_handler(p1);
  OutputDebug(L"original keyboard handler = %p\n", p1);
  OutputDebug(L"keyboard handler = %p\n", keyboard_handler);

  return (int)keyboard_handler;
  
    
    //return p_get_keyboard_handler(p1);
}

int CEF_CALLBACK hook_get_load_handler(void* p1) {
  int* load_handler = (int*)p_get_load_handler(p1);
  OutputDebug(L"load_handler = %p\n", load_handler);
  return (int)load_handler;
}

int CEF_CALLBACK hook_get_context_menu_handler(void* p1) {
  int* context_menu_handler = (int*)p_get_context_menu_handler(p1);
  OutputDebug(L"_cef_context_menu_handler_t = %p\n", context_menu_handler);




  return (int)context_menu_handler;

}

int CEF_CALLBACK hook_get_render_handler(void* p1) {
  // get _cef_render_handler_t
  int* render = (int*)p_get_render_handler(p1);
  //OutputDebug(L"render = %p\n", render);

  //DebugBreak();
  //OutputDebug(L"render[6] %p\n", render[6]);
  static bool once = 0;
  //if (!once) {
  if (1){
    ori_p_get_screen_info = (type_get_screen_info)render[6];

    // test
    // ori_p_get_screen_info = (type_get_screen_info)0x6E9172D5;

    render[6] = (int)&hook_get_screen_info;
    //once = !once;
  }
 

  return (int)render;
}
int CEF_CALLBACK hook_get_screen_info(void* p1, void* p2, void* p3) {
  int result = ori_p_get_screen_info(p1, p2, p3);

  OutputDebug(L"hook_get_screen_info trace\n");

  int* browser = (int*)p2;
  OutputDebug(L"browser = %p\n", browser);

  // size_t size = browser[0];
  // if (size != 0x64) {
  //  OutputDebug(L"Size check invalid\n");
  //  return (int)ori_p_get_screen_info(p1, p2, p3);
  //}

  //__try {
  //  func = (type_get_host)browser[4];
  //} __except (1) {
  //  return (int)ori_p_get_screen_info(p1, p2, p3);
  //}

  // DebugBreak();
  type_get_keyboard_handler func =
      (type_get_keyboard_handler)browser[4];  //就这句代码会引发崩溃

  // type_get_host func = (type_get_host)0x10984D3E;
  // OutputDebug(L"get_host %p\n", func);
  int* host = (int*)func((void*)browser);
  OutputDebug(L"host = %p\n", host);

  size_t size = host[0];
  if (size != 0xC8) {
    OutputDebug(L"Size check invalid\n");
  }

  // OutputDebug(L"ori_p_get_screen_info in hook_get_screen_info %p\n",
  //            ori_p_get_screen_info);
  return result;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      OutputDebug(L"hk_mailmaster DLL_PROCESS_ATTACH\n");

      const void* get_screen_info =
          Sig::find(GetModuleHandle(L"mailmaster.dll"), 13564928,
                    //"55 8b ec 51 83 65 fc 00 8b 45 08 56 57 85 C0 75 05");
                    "55 8B EC 51 83 65 FC 00 8B 45 08 56 57 85 C0 75 04 33 C0 EB 77");
      if (!get_screen_info) {
        OutputDebug(L"cant find get_screen_info!\n");
        return false;
      }
      OutputDebug(L"get_screen_info %p\n", get_screen_info);

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

      KStatus = MH_CreateHook((LPVOID)get_screen_info, sighook_get_screen_info,
                              (LPVOID*)&ori_sighook_get_screen_info);

      //MH_EnableHook(p_cef_browser_host_create_browser);
      MH_EnableHook((LPVOID)get_screen_info);

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

void run_dev_tools(void* host, void* api_address);
    //a1 _cef_render_handler_t
//a2 _cef_browser_t
int CEF_CALLBACK sighook_get_screen_info(int* a1, int a2, int a3, int a4) {
  //DebugBreak();
  type_get_keyboard_handler get_host = (type_get_keyboard_handler)((int*)a2)[4]; 
  OutputDebug(L"get_host %p\n", a2);

  int* host = (int*)get_host((void*)a2);
  OutputDebug(L"host %p\n", host);

  type_show_dev_tools show_dev_tools = (type_show_dev_tools)host[20];
  OutputDebug(L"show_dev_tools %p\n", show_dev_tools);

   cef_window_info_t windowInfo{};
  cef_browser_settings_t settings{};
  cef_point_t point{};
  cef_client_t client{};
  SetAsPopup(&windowInfo);
  //show_dev_tools(host, &windowInfo, &client, &settings, &point);
  show_dev_tools(host, &windowInfo,0, &settings, &point);
  static bool run = false;
  //if (!run) {
    //std::thread t(run_dev_tools, host, show_dev_tools);
    //t.detach();
    //run = true;
  //}
  return ori_sighook_get_screen_info(a1,a2,a3,a4);
}

void run_dev_tools(void* host,void* api_address) {
  std::this_thread::sleep_for(std::chrono::seconds(5));

  cef_window_info_t windowInfo{};
  cef_browser_settings_t settings{};
  cef_point_t point{};
  type_show_dev_tools show_dev_tools = (type_show_dev_tools)api_address; 
  OutputDebug(L"call show_dev_tools\n");
  show_dev_tools(host, &windowInfo, 0, &settings, &point);
}
