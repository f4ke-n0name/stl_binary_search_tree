#include <iostream>

#include "lib/bst.h"

int main() {
  // bst<int, InOrder, std::greater<int>> a, c;
  //   bst<int, InOrder> b = a;
  //   c = a;
  //   std::cout << b.max_size() << ' ' << c.size();
  int a = 4;
  int b = 5;
  b = a;
  a = 3;
  std::cout << b;
  return 0;
}