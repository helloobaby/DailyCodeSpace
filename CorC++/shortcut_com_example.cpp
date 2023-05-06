//http://chokuto.ifdef.jp/urawaza/com/shell.html

//#include "stdafx.h"
#include "windows.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"

HRESULT CreateLink(LPCWSTR lpszPathObj, LPCSTR lpszPathLink, LPCWSTR lpszDesc) {
  HRESULT hres;
  IShellLink* psl;

  // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
  // has already been called.
  // 这个接口存在的DLL必须由RegSvr32.exe注册过的
  // 计算机\HKEY_CLASSES_ROOT\CLSID
  // 然后在上面注册表键中可以找到相应的
  /*   ; シェルリンクオブジェクトのクラスID
   #define CLSID_ShellLink   "{00021401-0000-0000-C000-000000000046}"

   ; IShellLink インターフェースのインターフェースID
   #define IID_IShellLinkA   "{000214EE-0000-0000-C000-000000000046}"*/

  // 代码最终是进入到windows.storage.dll
  hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                          IID_IShellLink, (LPVOID*)&psl);
  if (SUCCEEDED(hres)) {
    IPersistFile* ppf;

    // Set the path to the shortcut target and add the description.
    psl->SetPath(lpszPathObj);
    psl->SetDescription(lpszDesc);

    // Query IShellLink for the IPersistFile interface, used for saving the
    // shortcut in persistent storage.
    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

    if (SUCCEEDED(hres)) {
      WCHAR wsz[MAX_PATH];

      // Ensure that the string is Unicode.
      MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);

      // Add code here to check return value from MultiByteWideChar
      // for success.

      // Save the link by calling IPersistFile::Save.
      hres = ppf->Save(wsz, TRUE);
      ppf->Release();
    }
    psl->Release();
  }
  return hres;
}

// COM函数需要依赖ole32.dll
int main() {
  HRESULT hres;
  hres = CoInitialize(0);
  if (!SUCCEEDED(hres)) return -1;
  hres = CreateLink(LR"(D:\Program Files\IDA Freeware 8.2\ida64.exe)",
                    R"(C:\Users\asdf\Desktop\IDA8.2.lnk)", L"IDA");
  if (!SUCCEEDED(hres)) return -2;

  

  CoUninitialize();
  return 0;
}
