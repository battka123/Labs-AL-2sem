// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

template <class T>
class Polynomial {
  // Здесь хранятся коэффициенты
  std::vector<T> data;

 public:
  // Деструктор
  ~Polynomial() = default;
  // Конструктор по умолчанию
  Polynomial() = default;
  // Конструктор со значением - вектор из типа T
  explicit Polynomial(const std::vector<T>& coefs) { data = coefs; }
  // Конструктор копирования
  Polynomial(const Polynomial& other) { data = other.data; }
  // Конструктор перемещения
  Polynomial(Polynomial&& other) noexcept { data = std::move(other.data); }

  Polynomial& operator=(const Polynomial& other) {
    data = other.data;
    return *this;
  }
  bool operator==(const Polynomial& other) const { return data == other.data; }
  bool operator!=(const Polynomial& other) const { return data != other.data; }
  // Оператор +=
  Polynomial& operator+=(const Polynomial& other) {
    if (data.size() < other.data.size()) data.resize(other.data.size());
    for (std::size_t i = 0; i < other.data.size(); ++i)
      data[i] += other.data[i];
    return *this;
  }
  // Оператор +
  Polynomial operator+(const Polynomial& other) const {
    Polynomial result(*this);
    result += other;
    return result;
  }
  // Оператор -=
  Polynomial& operator-=(const Polynomial& other) {
    if (data.size() < other.data.size()) data.resize(other.data.size());
    for (std::size_t i = 0; i < other.data.size(); ++i)
      data[i] -= other.data[i];
    return *this;
  }
  // Оператор -
  Polynomial operator-(const Polynomial& other) const {
    Polynomial result(*this);
    result -= other;
    return result;
  }
  // Оператор *= для матриц
  Polynomial& operator*=(const Polynomial& other) {
    std::vector<T> result_coeffs(data.size() + other.data.size() - 1);
    for (std::size_t i = 0; i < data.size(); ++i) {
      for (std::size_t j = 0; j < other.data.size(); ++j) {
        result_coeffs[i + j] += data[i] * other.data[j];
      }
    }
    data = result_coeffs;
    return *this;
  }
  // Оператор * для матриц
  Polynomial operator*(const Polynomial& other) const {
    Polynomial result(*this);
    result *= other;
    return result;
  }
  // Оператор *= для константы
  Polynomial& operator*=(const T& k) {
    for (auto& c : data) c *= k;
    return *this;
  }
  // Оператор * для константы
  Polynomial operator*(const T& k) const {
    Polynomial result(*this);
    result *= k;
    return result;
  }
  // Метод для нахождения степени
  int Degree() const {
    int degree = data.size() - 1;
    while (degree >= 0 && data[degree] == 0) --degree;
    return degree;
  }
  Polynomial<T> operator/=(const Polynomial& rhs) {
    if (this->data.size() < rhs.data.size()) {
      this->data = {0};
      return *this;
    }
    std::vector<T> vec1 = this->data;
    std::vector<T> vec2 = rhs.data;
    std::vector<T> res;

    while (vec1.size() >= vec2.size()) {
      T mult = vec1[0] / vec2[0];
      res.push_back(mult);
      for (size_t j = 0; j < vec2.size(); ++j) {
        vec1[j] = vec1[j] - mult * vec2[j];
      }
      vec1.erase(vec1.begin());
    }
    this->data = res;
    return *this;
  }
  // Оператор /
  Polynomial operator/(const Polynomial& other) const {
    Polynomial result(*this);
    result /= other;
    return result;
  }
  // Оператор %=
  Polynomial<T> operator%=(const Polynomial& rhs) {
    if (this->data.size() < rhs.data.size()) {
      this->data = {0};
      return *this;
    }
    std::vector<T> vec1 = this->data;
    std::vector<T> vec2 = rhs.data;
    std::vector<T> res;

    while (vec1.size() >= vec2.size()) {
      T mult = vec1[0] % vec2[0];
      res.push_back(mult);
      for (size_t j = 0; j < vec2.size(); ++j) {
        vec1[j] = vec1[j] - mult * vec2[j];
      }
      vec1.erase(vec1.begin());
    }
    this->data = res;
    return *this;
  }
  // Оператор %
  Polynomial operator%(const Polynomial& other) const {
    Polynomial result(*this);
    result %= other;
    return result;
  }
  // Метод для получения коэффициента при deg(x) = n
  T Coeff(std::size_t i) const {
    return i < data.size() ? data[i] : static_cast<T>(0);
  }
  // Метод для установки коэффицинта при deg(x) = n
  void SetCoeff(std::size_t i, const T& value) {
    if (i >= data.size()) data.resize(i + 1, static_cast<T>(0));
    data[i] = value;
  }
  // Метод для вычисления полинома в точке
  T operator()(const T& x) const {
    T result = 0;
    for (int i = Degree(); i >= 0; --i) result = result * x + data[i];
    return result;
  }
};

#endif  // INCLUDE_POLYNOMIAL_HPP_
