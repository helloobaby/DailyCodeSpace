#pragma once
#pragma warning(disable:4005)
#include"phnt_windows.h"
#include"phnt.h"

#include <iostream>

int main()
{
    HMODULE h = LoadLibrary(L"ntdll.dll");
    PVOID p = GetProcAddress(h, "wine_get_version");
    if (p != NULL) {
        printf("wine?\n");
    }
    else
        printf("native windows?\n");
    system("pause");
    return 0;
}

