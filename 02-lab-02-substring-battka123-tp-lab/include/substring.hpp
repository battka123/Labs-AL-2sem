// Copyright 2023 Ivan <i.suchin@yandex.ru>

#ifndef INCLUDE_SUBSTRING_HPP_
#define INCLUDE_SUBSTRING_HPP_
#include <string>
#include <vector>

size_t str_find(const std::string& str, const std::string& substr);
size_t rk_find(const std::string& str, const std::string& substr);
size_t kmp_find(const std::string& str, const std::string& substr);

#endif  // INCLUDE_SUBSTRING_HPP_
