#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <ShellScalingApi.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#pragma comment(lib, "Shcore.lib")

using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const int X0 = 120;
const int Y0 = 50;
const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

wstring kBmpPath;
int kAlpha;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  wstringstream ss(pCmdLine);
  vector<wstring> words;
  wstring word;
  ss >> kBmpPath;
  ss >> kAlpha;

  kBmpPath.erase(std::find_if(kBmpPath.begin(), kBmpPath.end(), [&](wchar_t c) {
    if (c == L'\"')
      return true;
    else
      return false;
  })
      );

    kBmpPath.erase(std::find_if(kBmpPath.begin(), kBmpPath.end(), [&](wchar_t c) {
    if (c == L'\"')
      return true;
    else
      return false;
  }));

  HWND hWnd;
  MSG msg;
  TCHAR lpszClassName[] = TEXT("CcWaterMarkWindow");

  // DPI自适应好像没用啊
  SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = lpszClassName;

  RegisterClass(&wc);

  // WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT
  hWnd =
      CreateWindow(lpszClassName, TEXT("CcWaterMarkWindow"), WS_EX_NOACTIVATE,
                   X0, Y0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

  // hWnd = CreateWindowEx(
  //    WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
  //    L"CcWaterMarkWindow", L"CcWaterMarkWindow", WS_POPUP, CW_USEDEFAULT, 0,
  //    CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

  ::ShowWindow(hWnd, SW_SHOWNORMAL);
  ::UpdateWindow(hWnd);

  // 实现透明必须设置WS_EX_LAYERED标志
  LONG nRet = ::GetWindowLong(hWnd, GWL_EXSTYLE);
  nRet = nRet | WS_EX_LAYERED;
  ::SetWindowLong(hWnd, GWL_EXSTYLE, nRet);

  ::SetLayeredWindowAttributes(hWnd, 0, kAlpha,
                               LWA_ALPHA);  // 修改alpha值实现透明度变化

  // 不显示在任务栏中
  // SetWindowLong(hWnd, GWL_EXSTYLE,
  //              GetWindowLong(hWnd, GWL_EXSTYLE) ^ WS_EX_TOOLWINDOW);

  while (::GetMessage(&msg, NULL, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
  return msg.wParam;
}

//https://www.cnblogs.com/fangyukuan/archive/2012/04/18/2454660.html 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_LBUTTONDOWN: {
    } break;
    case WM_RBUTTONDOWN: {
    } break;
    case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
    case WM_PAINT:
      PAINTSTRUCT ps;
      HDC hdc;
      HBITMAP hbmp;  // 位图绘制对象句柄，模糊图像
      HDC mdc;
      hdc = BeginPaint(hWnd, &ps);
      mdc = CreateCompatibleDC(hdc);  // 创建兼容的缓存DC对象
      //加载位图
      hbmp = (HBITMAP)
          LoadImage(NULL,  // 模块实例句柄
                    kBmpPath.c_str(),  
                    IMAGE_BITMAP,  // 图片类型
                    600, 300,
                    LR_LOADFROMFILE  // 从路径处加载图片
          );
      if (hbmp == NULL) {
        char c[20] = {0};
        sprintf(c, "err: %d\n", GetLastError());
        MessageBoxA(0, c, 0, 0);
      }
      // 缓存DC（mdc）选择位图绘制对象（可以理解为将图片保存到mdc中）
      SelectObject(mdc, hbmp);
      BitBlt(hdc,  // 目的DC
             0, 0,
             600,  // 目的DC的 x，y 坐标
             300,
             mdc,     // 缓存DC
             0, 0,    // 缓存DC的x，y坐标
             SRCCOPY  // 粘贴方式
      );
      DeleteObject(hbmp);
      DeleteDC(mdc);
      EndPaint(hWnd, &ps);
      break;
    default:
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
  }
  return 0;
}
