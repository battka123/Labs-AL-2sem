// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <iostream>

#include "substring.hpp"
int main() {
  std::string str = "THIS IS A TEST TEXT";
  const char* substr = "TEST";

  std::cout << str_find(str, substr) << std::endl;
  std::cout << rk_find(str, substr) << std::endl;
  std::cout << kmp_find(str, substr) << std::endl;
  std::cout << str.find(substr) << std::endl;

  return 0;
}
