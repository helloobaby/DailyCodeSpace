#include <iostream>
#include <windows.h>
using namespace std;

const wchar_t* kDllPath =
LR"(C:\Users\sbb\Desktop\AntiDebug.dll)";

class IAntiDebug {
public:
	virtual int pad0() = 0;
	virtual int pad1() = 0;
	virtual int pad2() = 0;
	virtual int pad3() = 0;
	virtual int pad4() = 0;
};

class AntiDebug : public IAntiDebug{
public:
	int pad4() override;
};

using DllGetInterfaceType = int (__stdcall *)(const char* Buf1, int a2);

int AntiDebug::pad4() {
	printf("hello\n");
	return 0;
}

int main()
{    
	auto h = LoadLibrary(kDllPath);
	// 判断加载是否成功
	if (h == NULL) {
		return -1;
	}

	auto pfnDllGetInterface = (DllGetInterfaceType)GetProcAddress(h, "DllGetInterface");
	if (!pfnDllGetInterface)
		return -2;

	AntiDebug* AD = (AntiDebug*)pfnDllGetInterface("IAntiDebug", 0);
	AD->pad4();


	return 0;
}

