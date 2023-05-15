#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <iostream>
#include <memory>


class A{
  public:
    int a = 0;
    A(int n){this->a = n;}
};

int main()
{
  std::unique_ptr _A = std::make_unique<A>(2);
  //std::unique_ptr _B = _A; // 编译不通过
  std::unique_ptr _B = std::move(_A); //转让所有权可以
  return 0;
}
