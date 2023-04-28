#include <iostream>
#include <windows.h>
using namespace std;

template <typename Ret, typename... Args>
void test(Ret(*fn)(Args...),Ret k) {// Ret类型不能由隐式转换了,原因不知道,反正编译器这样设计
  cout << typeid(Ret).name();
  cout << endl;
  cout << typeid(k).name();
}


int main() {
  //test(&CreateFileA,0); //error
  test(&CreateFileA,(HANDLE)0);
  return 0;
}
