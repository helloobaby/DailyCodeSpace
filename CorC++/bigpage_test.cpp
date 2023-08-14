// big_page.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// secpol.msc -> 本地策略 -> 用户权限分配
// process hacker的工作集里还是可以看到
// 0x1eb4e600000, Private, 2,048 kB, RW, , 2,048 kB, 2,048 kB, , , 2,048 kB

#include <iostream>
#include <windows.h>

static int ModifyPrivilege(const wchar_t* szPrivilege, bool fEnable) {
  HRESULT hr = S_OK;
  TOKEN_PRIVILEGES NewState;
  LUID luid;
  HANDLE hToken = nullptr;

  // Open the process token for this process.
  if (!OpenProcessToken(GetCurrentProcess(),
                        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    return ERROR_FUNCTION_FAILED;
  }

  // Get the local unique ID for the privilege.
  if (!LookupPrivilegeValue(nullptr, szPrivilege, &luid)) {
    CloseHandle(hToken);
    return ERROR_FUNCTION_FAILED;
  }

  // std::cout << luid.HighPart << " " << luid.LowPart << std::endl;

  // Assign values to the TOKEN_PRIVILEGE structure.
  NewState.PrivilegeCount = 1;
  NewState.Privileges[0].Luid = luid;
  NewState.Privileges[0].Attributes = (fEnable ? SE_PRIVILEGE_ENABLED : 0);

  // Adjust the token privilege.
  if (!AdjustTokenPrivileges(hToken, FALSE, &NewState, 0, nullptr, nullptr)) {
    hr = ERROR_FUNCTION_FAILED;
  }

  // Close the handle.
  CloseHandle(hToken);

  return hr;
}
int main() {
  // 需要组策略中打开权限
  //DebugBreak();
  ModifyPrivilege(SE_LOCK_MEMORY_NAME, true);
  std::cout << std::hex << GetLargePageMinimum() << std::endl;
  //DWORD WantAddress = 0x100000;
  SIZE_T pageSize = GetLargePageMinimum();
      std::cout << std::hex
            << VirtualAlloc(0, pageSize,
                            MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES,
                            PAGE_READWRITE)
            << std::endl;
  std::cout << GetLastError() << std::endl;
  getchar();
  return 0;
  
}

