// Copyright 2023 Ivan i.suschin@yandex.ru
#include <fstream>

#include "string.hpp"

int main() {
  String string;                  // создал пустую строку
  String string_2("i`m string");  // создал строку
  std::cout << string << std::endl;
  std::cout << string_2 << std::endl;
  String string_3(string_2);  // передал значение 2 строки к 3
  string_3[0] = '5';  // Поменял значение 1 символа
  std::cout << string_3 << std::endl;
  string_2 += "ABC";  // Прибавлять к строке
  std::cout << string_3 << std::endl;
  string_2 *= 3;  // Умножать строки
  std::cout << string_3 << std::endl;
  string_3.Replace('5', 'I');  // Заменять символ
  std::cout << string_3 << std::endl;
  std::cout << string_3.Find(" ")
            << std::endl;  // Найти индек символа, если его нет выводит -1
  std::cout << string_2.Size() << std::endl;  // Выводит размер строки
  String s("  ___ABC___!!!");
  std::cout << s << std::endl;
  // Удалять слева и справа похожие символы
  s.LTrim(' ');
  std::cout << string_3 << std::endl;
  s.RTrim('!');
  std::cout << string_3 << std::endl;
  // выводить в файл
  std::ofstream fout("main.txt");
  fout << s;
  fout.close();
  s.swap(string_3);  // менять строки местами
  std::cout << string_3 << std::endl;
  return 1;
}
