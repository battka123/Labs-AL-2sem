// Copyright 2023 Ivan i.suschin@yandex.ru

#ifndef INCLUDE_STRING_HPP_
#define INCLUDE_STRING_HPP_

#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

class String {
 public:
  ~String();

  String();

  String(const String& rhs);

  explicit String(const char* data);

  String& operator=(const String& rhs);

  String& operator+=(const char* rhs);
  String& operator+=(const String& rhs);

  String& operator*=(unsigned int m);

  bool operator==(const String& rhs) const;

  bool operator<(const String& rhs) const;

  size_t Find(const char* substr) const;
  size_t Find(const String& substr) const;

  void Replace(char oldSymbol, char newSymbol);

  size_t Size() const;

  bool Empty() const;

  char operator[](size_t index) const;

  char& operator[](size_t index);

  void RTrim(char symbol);
  void LTrim(char symbol);

  void swap(String& oth);

  friend std::ostream& operator<<(std::ostream&, const String&);
  friend bool operator==(const char* a, const String& b);

 private:
  char* Data;
};

String operator+(const String& a, const char* b);
String operator+(const String& a, const String& b);

String operator*(const String& a, unsigned int b);

bool operator!=(const String& a, const String& b);

bool operator>(const String& a, const String& b);

std::ostream& operator<<(std::ostream& out, const String& str);

#endif  // INCLUDE_STRING_HPP_
