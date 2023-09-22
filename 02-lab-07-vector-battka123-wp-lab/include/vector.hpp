// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include <stdexcept>
#include <utility>

template <class T>
class vector {
 public:
  vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

  explicit vector(size_t size, const T& value = T())
      : m_size(size), m_capacity(size) {
    m_data = new T[size];

    for (size_t i = 0; i < size; i++) m_data[i] = value;
  }

  vector(const vector& other)
      : m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = new T[m_capacity];

    for (size_t i = 0; i < m_size; i++) m_data[i] = other.m_data[i];
  }

  ~vector() {
    clear();
    delete[] m_data;
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      clear();

      if (m_capacity < other.m_size) {
        delete[] m_data;
        m_data = new T[other.m_capacity];
        m_capacity = other.m_capacity;
      }

      for (size_t i = 0; i < other.m_size; i++) m_data[i] = other.m_data[i];

      m_size = other.m_size;
    }
    return *this;
  }

  T& operator[](size_t index) { return m_data[index]; }

  const T& operator[](size_t index) const { return m_data[index]; }

  T& at(size_t index) {
    if (index < m_size)
      return m_data[index];
    else
      throw std::out_of_range("vector::at: Index out of range.");
  }

  const T& at(size_t index) const {
    if (index < m_size)
      return m_data[index];
    else
      throw std::out_of_range("vector::at: Index out of range.");
  }

  T& front() { return m_data[0]; }

  const T& front() const { return m_data[0]; }

  T& back() { return m_data[m_size - 1]; }

  const T& back() const { return m_data[m_size - 1]; }

  T* data() { return m_data; }

  const T* data() const { return m_data; }

  T* begin() { return m_data; }

  const T* begin() const { return m_data; }

  T* end() { return m_data + m_size; }

  const T* end() const { return m_data + m_size; }

  bool empty() const { return m_size == 0; }

  size_t size() const { return m_size; }

  void reserve(size_t new_capacity) {
    if (new_capacity > m_capacity) {
      m_capacity = new_capacity;
      T* new_data = new T[m_capacity];

      for (size_t i = 0; i < m_size; i++) new_data[i] = m_data[i];

      delete[] m_data;
      m_data = new_data;
    }
  }

  size_t capacity() const { return m_capacity; }

  void clear() {
    for (size_t i = 0; i < m_size; i++) m_data[i].~T();
    m_size = 0;
    m_capacity = 0;
  }

  void insert(size_t index, const T& value) {
    if (m_size >= m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);

    for (size_t i = m_size; i > index; i--) m_data[i] = m_data[i - 1];

    m_data[index] = value;
    m_size++;
  }

  void push_back(const T& value) { insert(m_size, value); }

  void pop_back() {
    if (m_size > 0) {
      m_data[m_size - 1].~T();
      m_size--;
    }
  }

  void swap(vector& other) {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

 private:
  T* m_data;
  size_t m_size;
  size_t m_capacity;
};

#endif  // INCLUDE_VECTOR_HPP_
