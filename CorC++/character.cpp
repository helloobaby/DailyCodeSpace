// IO_STATUS_BLOCK and printf
#include"phnt/phnt_windows.h"
#include"phnt/phnt.h"
#include <cstdio>
#include <iostream>
//https://github.com/n00bes/inline-syscall
#include "inline_syscall.hpp"
int main() {
    std::wcout.imbue(std::locale("chs")); //output Chinese
    const char* nihao = "你好";
    const wchar_t* lnihao = L"你好গা";
    for (int i = 0; i < strlen(nihao); i++)
        printf("%x ", (unsigned char)nihao[i]);
    printf("\n");

    for (int i = 0; i < wcslen(lnihao); i++)
        printf("%x ", (wchar_t)lnihao[i]);
    printf("\n");

    std::cout << lnihao[0] << std::endl;
    std::cout << lnihao[3] << std::endl;

    std::wcout << lnihao[0] << std::endl; //[你]
    std::wcout << lnihao[1] << std::endl; //[好]
    std::wcout << lnihao[2] << std::endl; //没输出,因为গা字符占lnihao[3],lnihao[4]

    std::wstring wsnihao = lnihao;
    std::cout << "sizeof wstring " << wsnihao.size() << std::endl; // 4
    std::cout << "length wstring " << wsnihao.length() << std::endl;// 4 

    // 那么如何输出大于2字节的unicode字符呢
}