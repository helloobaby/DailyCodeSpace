// HRESULT返回值
//https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values

#include <iostream>
#include <windows.h>
using namespace std;

const wchar_t* kDllPath =
LR"(D:\Download\1.0.70.988\1.0.70.988\AntiDebug.dll)";

using DllGetInterfaceType = HRESULT (__stdcall *)(const char* Buf1, void* a2);
using AntiDebugStartType = int (__stdcall*)(void* _this, int unknow);
using AntiDebugStartType2 = int (__stdcall*)(void* _this);

int main() {
  auto h = LoadLibrary(kDllPath);
  // 判断加载是否成功
  if (h == NULL) {
    return -1;
  }

  GUID uuid;
  uuid.Data1 = 0xEC1330C1;
  *(unsigned int*)&uuid.Data2 = 0x4B31E3AE;
  *(unsigned int*)uuid.Data4 = 0xC3E45885;
  *(unsigned int*)&uuid.Data4[4] = 0xADC42BB4;

  auto pfnDllGetInterface =
      (DllGetInterfaceType)GetProcAddress(h, "DllGetInterface");
  if (!pfnDllGetInterface) return -2;

  void* ppv;

  HRESULT res = pfnDllGetInterface((const char*)&uuid, &ppv);
  printf("%p\n", ppv);

  //ppv[0]是下面这个虚表
//  .rdata:0FE202C0 ; const ATL::CComObject<class AntiDebug>::`vftable'{for `IAntiDebug'}
//.rdata:0FE202C0 ??_7?$CComObject@VAntiDebug@@@ATL@@6BIAntiDebug@@@

  //PVOID DecodedPtr = DecodePointer((PVOID)0xEC1330C1);
  //printf("%p\n", DecodedPtr);


  void** vtable = *(void***)(((uint32_t)ppv - sizeof(void*)));
  printf("%p\n", vtable);

  //vtable = 0FE20400
//  .rdata:0FE20400 ??_7?$CComObject@VAntiDebug@@@ATL@@6B@ dd offset sub_FCCEA20
//.rdata:0FE20400                                         ; DATA XREF: AntiDebug_Constructor+38↑o
//.rdata:0FE20400                                         ; sub_FCCE8F0+29↑o
//.rdata:0FE20400                                         ; 虚函数表
//.rdata:0FE20404                 dd offset sub_FCCE980
//.rdata:0FE20408                 dd offset sub_FCCE9A0
//.rdata:0FE2040C                 dd offset sub_FCC57C0   ; AntiDebug start?
//.rdata:0FE20410                 dd offset sub_FCC5BB0   ; AntiDebug end?
//.rdata:0FE20414                 dd offset sub_FCBCBF0   ; return 0
//.rdata:0FE20418                 dd offset sub_FCCEAC0   ; 好像是释放资源的

  AntiDebugStartType AntiDebugStart = (AntiDebugStartType)vtable[3]; 
  printf("%p\n", AntiDebugStart);

  //AntiDebugStart == sub_FCC57C0

  int br = AntiDebugStart((void*)((uint32_t)ppv - sizeof(void*)), 0);
  printf("result %d\n", br);

  //AntiDebugStartType2 AntiDebugStart2 = (AntiDebugStartType2)vtable[4]; 
  //printf("result %p\n", AntiDebugStart2);
  //br = AntiDebugStart2((void*)((uint32_t)ppv - sizeof(void*)));
  //printf("result %d\n", br);

  getchar();
  return 0;
}
