#include <iostream>
#include <windows.h>
using namespace std;

template <typename Ret, typename... Args>
static inline auto spoof_call(
	const void* trampoline,
	Ret(*fn)(Args...), // 提供一个已有函数原型推导参数类型Args和返回类型Ret
	Args... args)
	-> Ret {
  cout << typeid(Ret).name() << " ";
  Ret r = 0;
  return r;
} 

// 打印出参数包中参数被自动推导的类型
template<typename Arg>
void print_param_packedtype(const Arg& arg){
    //std::cout<<arg<<std::endl;
  cout << typeid(Arg).name() << " ";
}

template<typename Arg,typename ...Args>
void print_param_packedtype(const Arg& arg,const Args& ...args){
    //std::cout<<arg<<" ";
  cout << typeid(Arg).name() << endl;
    print_param_packedtype(args...); //递归解包
}
//


int main() {
  spoof_call(nullptr, &CreateFileA, "test.txt", (GENERIC_READ | GENERIC_WRITE),
             (DWORD)(FILE_SHARE_WRITE | FILE_SHARE_READ),
             (LPSECURITY_ATTRIBUTES)NULL, (DWORD)CREATE_ALWAYS,
             (DWORD)FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

  print_param_packedtype("test.txt", (GENERIC_READ | GENERIC_WRITE),
                         (FILE_SHARE_WRITE | FILE_SHARE_READ),
                        NULL, CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL, NULL);
  return 0;
}
