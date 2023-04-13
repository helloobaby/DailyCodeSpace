#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// 这头文件只能放最前面
#include <doctest/doctest.h>

#include <cstdio>
#include <cassert>
#include <windows.h>
#include <locale>
// 前面要加上windows.h,有隐藏依赖
#include <imagehlp.h>
#pragma comment(lib,"Imagehlp.lib")

// 
#include "D:\Src\DailyCodeSpace\CorC++\output_win32_error.h"

static int ModifyPrivilege(const wchar_t* szPrivilege, bool fEnable) {
	HRESULT hr = S_OK;
	TOKEN_PRIVILEGES NewState;
	LUID luid;
	HANDLE hToken = nullptr;

	// Open the process token for this process.
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
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

TEST_CASE("MapFileAndCheckSum") {
    DWORD HeaderSum;
    DWORD CheckSum;
    CHECK(MapFileAndCheckSumW(LR"(C:\Users\sbb\Desktop\Procmon64.exe)", &HeaderSum, &CheckSum) == CHECKSUM_SUCCESS);
    printf("%d %d\n", HeaderSum, CheckSum);
}

TEST_CASE("TouchFileTimes") {
    // open file test.txt
    HANDLE hFile = CreateFileW(LR"(C:\Users\sbb\Desktop\Procmon64.exe)", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // check status
    if (hFile == INVALID_HANDLE_VALUE) {
		printf("CreateFile failed (%d)\n", GetLastError());
		return;
	}

    SYSTEMTIME st;
    GetSystemTime(&st);
    st.wYear = 1995;
    //CHECK(TouchFileTimes(hFile,&st) == TRUE);

}

TEST_CASE("Cert") {
    std::locale::global(std::locale(""));

	assert(ModifyPrivilege(SE_BACKUP_NAME, true) == S_OK);
	assert(ModifyPrivilege(SE_RESTORE_NAME, true) == S_OK);
    HANDLE hFile = CreateFileW(LR"(C:\Users\sbb\Desktop\Procmon64.exe)", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS , NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        DisplayError(GetLastError());
        return;
    }
    DWORD count;
    DWORD indices[64]{};
    CHECK(ImageEnumerateCertificates(hFile, CERT_SECTION_TYPE_ANY, &count, indices, _countof(indices)));

    for (DWORD i = 0; i < count; i++) {
		WIN_CERTIFICATE wc{};
        if (ImageGetCertificateHeader(hFile, indices[i], &wc)) {
			//WIN_CERT_TYPE_PKCS_SIGNED_DATA
            printf("%d\n", wc.wCertificateType);
        }
	}



}