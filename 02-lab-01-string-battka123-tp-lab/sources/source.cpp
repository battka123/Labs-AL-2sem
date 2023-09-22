// Copyright 2023 Ivan i.suschin@yandex.ru
#include "string.hpp"
String::~String() { delete[] Data; }
String::String() { Data = nullptr; }

String::String(const char* data) {
  Data = new char[strlen(data) + 1];
  for (size_t i = 0; i < strlen(data) + 1; ++i) Data[i] = data[i];
}

String::String(const String& rhs) {
  Data = new char[strlen(rhs.Data) + 1];
  for (size_t i = 0; i < strlen(rhs.Data) + 1; ++i) Data[i] = rhs.Data[i];
}

String& String::operator=(const String& rhs) {
  if (this != &rhs) {
    delete[] Data;
    Data = new char[strlen(rhs.Data) + 1];
    for (size_t i = 0; i < strlen(rhs.Data) + 1; ++i) Data[i] = rhs.Data[i];
  }
  return *this;
}

String& String::operator+=(const char* rhs) {
  const size_t size = strlen(Data) + strlen(rhs) + 1;
  char *temp = new char[size];
  snprintf(temp, size, "%s%s", Data, rhs);
  delete[] Data;
  Data = temp;
  return *this;
}
String& String::operator+=(const String& rhs) {
  const size_t size = strlen(Data) + strlen(rhs.Data) + 1;
  char *temp = new char[size];
  snprintf(temp, size, "%s%s", Data, rhs.Data);
  delete[] Data;
  Data = temp;
  return *this;
}

String& String::operator*=(unsigned int m) {
  String result = *this;
  for (size_t i = 0; i < m; ++i) result += *this;
  *this = result;
  return *this;
}

bool String::operator==(const String& rhs) const {
  return (strcmp(Data, rhs.Data) == 0);
}

bool String::operator<(const String& rhs) const {
  return Size() < strlen(rhs.Data);
}

size_t String::Find(const char* substr) const {
  size_t rem;
  for (size_t i = 0; i < Size(); ++i) {
    if (Data[i] == substr[0]) {
      for (size_t j = 0; j < strlen(substr); ++j) {
        if (Data[i + j] != substr[j]) break;
        rem = j;
      }
      if (rem == strlen(substr) - 1) return i;
      i += rem;
    }
  }
  return -1;
}

size_t String::Find(const String& substr) const {
  size_t rem;
  for (size_t i = 0; i < Size(); ++i) {
    if (Data[i] == substr[0]) {
      for (size_t j = 0; j < strlen(substr.Data); ++j) {
        if (Data[i + j] != substr[j]) break;
        rem = j;
      }
      if (rem == strlen(substr.Data) - 1) return i;
      i += rem;
    }
  }
  return -1;
}

void String::Replace(char oldSymbol, char newSymbol) {
  for (size_t i = 0; i < Size(); ++i) {
    if (Data[i] == oldSymbol) Data[i] = newSymbol;
  }
}

size_t String::Size() const {
  return this->Data != nullptr ? strlen(this->Data) : 0;
}

bool String::Empty() const {
  if (Data == nullptr) return true;
  return false;
}
char String::operator[](size_t index) const { return Data[index]; }

char& String::operator[](size_t index) { return Data[index]; }

void String::RTrim(char symbol) {
  size_t counter = 0;

  for (int i = static_cast<int>(strlen(Data)) - 1; i >= 0; --i) {
    if (Data[i] != symbol) {
      break;
    }
    counter++;
  }
  size_t new_len = strlen(Data) - counter;

  if (counter != 0) {
    char* new_str = new char[new_len + 1];
    for (size_t i = 0; i < new_len; ++i) {
      new_str[i] = Data[i];
    }
    delete[] Data;
    new_str[new_len] = '\0';
    Data = new_str;
  }
}

void String::LTrim(char symbol) {
  size_t counter = 0;

  for (size_t i = 0; i < strlen(Data); ++i) {
    if (Data[i] != symbol) {
      break;
    }
    ++counter;
  }
  size_t new_len = strlen(Data) - counter;

  if (counter != 0) {
    char* new_str = new char[new_len + 1];
    for (size_t i = 0; i < new_len; ++i) {
      new_str[i] = Data[i + counter];
    }
    delete[] Data;
    new_str[new_len] = '\0';
    Data = new_str;
  }
}

void String::swap(String& oth) {
  char* str_2 = oth.Data;
  oth.Data = Data;
  Data = str_2;
}

String operator+(const String& a, const char* b) {
  String buf = a;
  buf += b;
  return buf;
}

String operator+(const String& a, const String& b) {
  String buf = a;
  buf += b;
  return buf;
}

String operator*(const String& a, unsigned int b) {
  String buf = a;
  buf *= (b - 1);
  return buf;
}

bool operator!=(const String& a, const String& b) {
  if (a == b) return false;
  return true;
}

bool operator==(const char* rhs, const String& rhs_2) {
  return (strcmp(rhs_2.Data, rhs) == 0);
}

bool operator>(const String& a, const String& b) {
  if (a < b || a == b) return false;
  return true;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  return out << str.Data;
}
