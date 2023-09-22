// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

#include <cmath>
#include <cstddef>
#include <iostream>
#include <utility>

template <class T>
class Matrix {
 public:
  T** _data = nullptr;
  size_t _rows = 0;
  size_t _columns = 0;

 public:
  // Деструктор
  ~Matrix() {
    for (unsigned int i = 0; i < _rows; i++) {
      delete[] _data[i];
    }
    delete[] _data;
  }
  // Конструктор со значениями
  Matrix(size_t n, size_t m) {
    for (unsigned int i = 0; i < _rows; i++) {
      delete[] _data[i];
    }

    delete[] _data;
    _rows = n;
    _columns = m;
    _data = new T*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
      _data[i] = new T[_columns];
      for (size_t j = 0; j < _columns; ++j) {
        _data[i][j] = 0;
      }
    }
  }
  // Конструктор копирования
  Matrix(const Matrix& other) {
    for (unsigned int i = 0; i < _rows; i++) {
      delete[] _data[i];
    }

    delete[] _data;
    _rows = other._rows;
    _columns = other._columns;
    _data = new T*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
      _data[i] = new T[_columns];
    }
    for (size_t i = 0; i < _rows; ++i) {
      for (size_t j = 0; j < _columns; ++j) {
        _data[i][j] = other._data[i][j];
      }
    }
  }
  // Операторы сравнения == и !=
  bool operator==(const Matrix& m) const {
    if (_rows != m._rows || _columns != m._columns) return false;
    for (size_t i = 0; i < _rows; ++i) {
      for (size_t j = 0; j < _columns; ++j) {
        if (_data[i][j] != m._data[i][j]) return false;
      }
    }
    return true;
  }

  bool operator!=(const Matrix& m) const {
    if (_rows != m._rows || _columns != m._columns) return true;
    for (size_t i = 0; i < _rows; ++i) {
      for (size_t j = 0; j < _columns; ++j) {
        if (_data[i][j] != m._data[i][j]) return true;
      }
    }
    return false;
  }
  // Оператор присваивания
  Matrix& operator=(const Matrix& other) {
    for (unsigned int i = 0; i < _rows; i++) {
      delete[] _data[i];
    }

    delete[] _data;
    _rows = other._rows;
    _columns = other._columns;
    _data = new T*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
      _data[i] = new T[_columns];
      for (size_t j = 0; j < _columns; ++j) {
        _data[i][j] = other._data[i][j];
      }
    }
    return *this;
  }
  // Операторы индексации
  T* operator[](size_t i) { return _data[i]; }

  const T* operator[](size_t i) const { return _data[i]; }

  size_t Rows() { return _rows; }

  size_t Cols() { return _columns; }
  // Оператор сложения
  Matrix operator+(const Matrix& m) {
    if (_rows != m._rows || _columns != m._columns) {
      for (unsigned int i = 0; i < _rows; i++) {
        delete[] _data[i];
      }

      delete[] _data;
      _rows = 0;
      _columns = 0;
      _data = nullptr;
      return *this;
    }
    for (size_t i = 0; i < m._rows; ++i) {
      for (size_t j = 0; j < m._columns; ++j) {
        _data[i][j] = m._data[i][j] + _data[i][j];
      }
    }
    return *this;
  }
  // Оператор вычитания
  Matrix operator-(const Matrix& m) {
    if (_rows != m._rows || _columns != m._columns) {
      for (unsigned int i = 0; i < _rows; i++) {
        delete[] _data[i];
      }

      delete[] _data;
      _rows = 0;
      _columns = 0;
      _data = nullptr;
      return *this;
    }

    for (size_t i = 0; i < m._rows; ++i) {
      for (size_t j = 0; j < m._columns; ++j) {
        _data[i][j] = _data[i][j] - m._data[i][j];
      }
    }
    return *this;
  }
  // Оператор умножения
  Matrix& operator*(const Matrix& other) {
    if (_columns != other._rows) {
      for (unsigned int i = 0; i < _rows; i++) {
        delete[] _data[i];
      }

      delete[] _data;
      _columns = 0;
      _rows = 0;
      _data = nullptr;
      return *this;
    }

    size_t rows_ = _rows;
    size_t columns_1 = _columns;
    size_t columns_2 = other._columns;
    T** data_ = new T*[rows_ + 2];

    for (size_t i = 0; i < rows_; ++i) {
      data_[i] = new T[columns_2 + 2];
      for (size_t j = 0; j < columns_2; ++j) {
        data_[i][j] = 0;
        for (size_t k = 0; k < columns_1; ++k) {
          data_[i][j] += _data[i][k] * other._data[k][j];
        }
      }
    }

    for (size_t i = 0; i < _rows; ++i) {
      delete[] _data[i];
    }

    delete[] _data;
    _columns = columns_2;
    _data = new T*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
      _data[i] = new T[_columns];
      for (size_t j = 0; j < _columns; ++j) {
        _data[i][j] = data_[i][j];
      }
    }

    for (size_t i = 0; i < _rows; ++i) {
      delete[] data_[i];
    }

    delete[] data_;
    return *this;
  }
  // Оператор инверсии
  Matrix<T> Inverse() const {
    Matrix<T> first_matrix_(*this);
    Matrix<T> second_matrix_(_rows, _rows);

    for (size_t i = 0; i < _rows; ++i) {
      second_matrix_[i][i] = 1.;
    }

    for (size_t k = 0; k < _rows; ++k) {
      size_t max_row = k;
      for (size_t i = k + 1; i < _rows; ++i) {
        if (std::abs(first_matrix_[i][k]) >
            std::abs(first_matrix_[max_row][k])) {
          max_row = i;
        }
      }

      if (max_row != k) {
        std::swap(first_matrix_._data[k], first_matrix_._data[max_row]);
        std::swap(second_matrix_._data[k], second_matrix_._data[max_row]);
      }

      T matr = first_matrix_[k][k];

      for (size_t j = k; j < _rows; ++j) {
        first_matrix_[k][j] /= matr;
      }

      for (size_t j = 0; j < _rows; ++j) {
        second_matrix_[k][j] /= matr;
      }

      for (size_t i = 0; i < _rows; ++i) {
        if (i == k) continue;
        T rem = first_matrix_[i][k];

        for (size_t j = k; j < _rows; ++j) {
          first_matrix_[i][j] -= rem * first_matrix_[k][j];
        }

        for (size_t j = 0; j < _rows; ++j) {
          second_matrix_[i][j] -= rem * second_matrix_[k][j];
        }
      }
    }
    return second_matrix_;
  }
};

#endif  // INCLUDE_MATRIX_HPP_
