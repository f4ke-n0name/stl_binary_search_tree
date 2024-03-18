#include <iostream>

#include "lib/bst.h"

// Протестировать свои функции
// Написать тесты
// подумать все ли варианты методов написаны

int main() {
  bst<int, InOrder, std::greater<int>> a, c;
  bst<int, InOrder , std::greater<int>> b = a;
  c = a;
  std::cout << b.max_size() << ' ' << c.size();
  return 0;
}