#include <iostream>
#include <windows.h>
using namespace std;

template<typename _T = float>
void test(_T p1) {
  cout << p1 << " ";
}

template<typename _T = DWORD>
void test2(_T p1) {
  cout << p1 << " ";
}

template<typename _T = HANDLE>
void test3(_T p1) {
	cout << p1 << " ";
}

int main() {
  test(4.0);// double 隐式转float
  test2(1);// int隐式转DWORD
  test3(0);// int转void*
  return 0;
}
