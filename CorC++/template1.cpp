#include <iostream>
using namespace std;

template <typename _T>
void test(float, _T p1) {
  printf("%d\n", p1);
}

struct ctest {
	template <typename First,
			typename Second,
			typename Third>
	static auto do_call(First p1,Second p2,Third p3) {
    cout << p1 << " " << p2 << " " << p3 << "\n";
  }
};


int main() {
  // float
  test(1.0f, 2);
  // double
  test(1.0, 2);

  ctest::template do_call(1.0, 2, 'c');
  ctest::do_call(1.0, 2, 'c');

  return 0;
}
