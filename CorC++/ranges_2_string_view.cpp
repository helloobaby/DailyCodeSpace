#include <iostream>
#include <ranges>
#include <string_view>
using namespace std;

const char* remoteAddress = "112.44.72.116:12224";

int main()
{ 
  auto range = string_view(remoteAddress) | ranges::views::split(':');
  for(const auto &sub_range : range) {
    cout << string_view(&*sub_range.begin(), ranges::distance(sub_range));
  }
   
  return 0;
}
