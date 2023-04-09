#include <iostream>
#include <windows.h>
// 包含NTSTATUS的头文件
#include <ntstatus.h>
using namespace std;

NTSTATUS MyNtTerminateProcess(
  HANDLE   ProcessHandle,
  NTSTATUS ExitStatus
);

int count = 0;
int main()
{
    // 输出当前进程PID
    cout << GetCurrentProcessId() << endl;



	// 获得NtTerminateProcess函数地址
    HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");
    FARPROC pNtTerminateProcess = GetProcAddress(hNtdll, "NtTerminateProcess");
    // 以16进制输出pNtTerminateProcess的值
    cout << hex << pNtTerminateProcess << endl;

    // 



    // 创建一个线程,每秒钟输出一个数字
    HANDLE hThread = CreateThread(NULL, 0, [](LPVOID lpParameter)->DWORD{
        while(1){
            cout << "Hello World" << endl;
            Sleep(1000);
        }
        return 0;
    }, NULL, 0, NULL);



    // 主线程等待上面那个线程结束
    WaitForSingleObject(hThread, INFINITE);







	return 0;
}

NTSTATUS MyNtTerminateProcess(
  HANDLE   ProcessHandle,
  NTSTATUS ExitStatus
){
    // 弹窗close
    MessageBox(NULL, L"close", L"close", MB_OK);
    return NTSTATUS_SUCCESS;
}