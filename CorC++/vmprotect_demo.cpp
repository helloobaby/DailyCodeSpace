#include<iostream>
#include<windows.h>
#include<intrin.h>

using namespace std;


int dummy_1 = 1;
int dummy_2 = 2;

int res = 0;

int cpuid[4];


int main()
{

    res = IsDebuggerPresent();

    printf("%d\n", res);

    res = dummy_1 + dummy_2;

    printf("%d\n", res);
    
    res = dummy_1 - dummy_2;

    printf("%d\n", res);

    res = dummy_1 * dummy_2;

    printf("%d\n", res);

    res = dummy_1 / dummy_2;

    printf("%d\n", res);

    res = dummy_1 << 1;

    printf("%d\n", res);

    res = dummy_1 >> 1;

    printf("%d\n", res);

    __cpuid(cpuid, 9);

    if (res == 3)
    {
        res = 0x111111;
    }
    else
        res = 0x777777;

    printf("%d\n", res);







    return 0;
}


