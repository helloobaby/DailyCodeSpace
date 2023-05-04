#include <iostream>
#include <memory>
#include <assert.h>

using namespace std;

#define version2

struct fa
{
#ifdef version2
  virtual void pure_test() = 0;
#endif  // version2

	virtual void f() { cout << "fa:f" << endl; }
};

struct son :public fa
{
	virtual void f() { cout << "son:f" << endl; fa::f();}
        virtual void pure_test() override{}
};

struct thr 
{
	virtual void f() { cout << "thr:f" << endl; }
};

typedef const struct	_s_RTTICompleteObjectLocator {
	unsigned long							signature;
	unsigned long							offset;
	unsigned long							cdOffset;
	int										pTypeDescriptor;	// Image relative offset of TypeDescriptor
	int										pClassDescriptor;	// Image relative offset of _RTTIClassHierarchyDescriptor
	int										pSelf;				// Image relative offset of this object
} _RTTICompleteObjectLocator;

int main()
{
	//IDA 8.2 free
//	.text:004129CF                 lea     ecx, [ebp+a]    ; this              栈
//.text:004129D2                 call    j_??0fa@@QAE@XZ ; fa::fa(void)        类构造函数

//	text:004120B0 ??0fa@@QAE@XZ   proc near               ; CODE XREF: fa::fa(void)↑j
//.text:004120B0
//.text:004120B0 this            = dword ptr -8
//.text:004120B0
//.text:004120B0                 push    ebp
//.text:004120B1                 mov     ebp, esp
//.text:004120B3                 sub     esp, 0CCh
//.text:004120B9                 push    ebx
//.text:004120BA                 push    esi
//.text:004120BB                 push    edi
//.text:004120BC                 mov     [ebp+this], ecx  //local.this = this(param)
//.text:004120BF                 mov     eax, [ebp+this]
//.text:004120C2                 mov     dword ptr [eax], offset ??_7fa@@6B@ ; const fa::`vftable' //虚函数表
//.text:004120C8                 mov     eax, [ebp+this] //构造函数的返回值是this指针
//.text:004120CB                 pop     edi
//.text:004120CC                 pop     esi
//.text:004120CD                 pop     ebx
//.text:004120CE                 mov     esp, ebp
//.text:004120D0                 pop     ebp
//.text:004120D1                 retn
//.text:004120D1 ??0fa@@QAE@XZ   endp


//	.rdata:00419B30                 dd offset ??_R4fa@@6B@  ; const fa::`RTTI Complete Object Locator'
//.rdata:00419B34 ; void (__cdecl *const fa::`vftable'[2])()
//.rdata:00419B34 ??_7fa@@6B@     dd offset j_?f@fa@@UAEXXZ
//.rdata:00419B34                                         ; DATA XREF: fa::fa(void)+12↑o
//.rdata:00419B34                                         ; fa::f(void)
//.rdata:00419B38                 dd 0


//	version2
//		.rdata:00419B2C ; struct struct fa:    (#classinformer)
//.rdata:00419B2C                 dd 0, offset ??_R4fa@@6B@ ; const fa::`RTTI Complete Object Locator'
//.rdata:00419B34 ; void (__cdecl *const fa::`vftable'[3])()
//.rdata:00419B34 ??_7fa@@6B@     dd offset j___purecall  ; DATA XREF: fa::fa(void)+12↑o //纯虚函数
//.rdata:00419B38                 dd offset j_?f@fa@@UAEXXZ ; fa::f(void)
//.rdata:00419B3C                 dd 2 dup(0)
//.rdata:00419B44                 dd 0


#ifndef version2
	fa a;
#endif
	son b;
	thr c;
#ifndef version2
	a.f();
	_RTTICompleteObjectLocator * p = (_RTTICompleteObjectLocator*)((*((void***)&a))[-1]);
#endif
	c.f();

	_RTTICompleteObjectLocator* p2 = (_RTTICompleteObjectLocator*)((*((void***)&b))[-1]);
	_RTTICompleteObjectLocator* p3 = (_RTTICompleteObjectLocator*)((*((void***)&c))[-1]);

	return 0;
}
