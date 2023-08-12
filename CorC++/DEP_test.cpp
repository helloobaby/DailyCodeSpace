// snippet_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <cassert>
int main()
{
    // https://learn.microsoft.com/en-us/cpp/build/reference/nxcompat-compatible-with-data-execution-prevention?view=msvc-170
    // 关掉DEP其实不需要调用这个函数,设置编译器链接属性就可以了
    // 这样没有执行属性的页面都可以执行shellcode
    //assert(SetProcessDEPPolicy(0),GetLastError());

    using func = void(*)();
    func p = (func)VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_READWRITE);
    assert(p && int("分配内存失败"));

    char src = 0xc3;
    memcpy(p, &src, 1);

    p();

    getchar();
    return 0;
}

