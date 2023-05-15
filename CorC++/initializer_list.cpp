#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <iostream>
#include <memory>
#include <initializer_list>


class A{
  public:
    int _a = 0;
    int _b = 0;
    A(int n,int m){this->_a = n;this->_b = m;}
    A(std::initializer_list<int> l){
      std::cout << l.size()<< std::endl;


    }
};

int main()
{
  A t = A(1,2);
  A t2 = A{1,2};
  return 0;
}
