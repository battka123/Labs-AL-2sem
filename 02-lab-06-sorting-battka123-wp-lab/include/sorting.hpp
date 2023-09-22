// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_SORTING_HPP_
#define INCLUDE_SORTING_HPP_

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template <class It, class Out, class Compare = std::less<>>
Out merge(It first1, It last1, It first2, It last2, Out out,
          Compare cmp = Compare{}) {
  while (first1 != last1 && first2 != last2) {
    if (cmp(*first1, *first2)) {
      *out++ = *first1++;
    } else {
      *out++ = *first2++;
    }
  }
  while (first1 != last1) {
    *out++ = *first1++;
  }
  while (first2 != last2) {
    *out++ = *first2++;
  }
  return out;
}

template <class It, class Out, class Compare = std::less<>>
Out merge_sort(It first, It last, Out out, Compare cmp = Compare{}) {
  std::vector<typename It::value_type> temp1, temp2, result;
  const auto distance = std::distance(first, last);
  result.emplace_back(*first);
  if (distance > 1) {
    const auto middle = std::next(first, distance / 2);
    merge_sort(first, middle, std::back_inserter(temp1), cmp);
    merge_sort(middle, last, std::back_inserter(temp2), cmp);
    result.clear();
    merge(temp1.begin(), temp1.end(), temp2.begin(),
          temp2.end(),
          std::back_inserter(result), cmp);
  }
  std::copy(result.begin(), result.end(), out);
  return out;
}

template <class It, class Compare = std::less<>>
void inplace_merge_sort(It first, It last, Compare cmp = Compare{}) {
  const auto distance = std::distance(first, last);
  if (distance > 1) {
    const auto middle = std::next(first, distance / 2);
    inplace_merge_sort(first, middle, cmp);
    inplace_merge_sort(middle, last, cmp);
    std::inplace_merge(first, middle, last, cmp);
  }
}

template <class It, class Compare = std::less<>>
void heapify(It first, It last, It base, size_t heap_size,
             Compare cmp = Compare{}) {
  It root = base;
  size_t distance = std::distance(first, root);
  It l = std::next(first, distance * 2 + 1);
  It r = std::next(first, distance * 2 + 2);
  if (distance * 2 + 1 < heap_size && cmp(*root, *l)) root = l;
  if (distance * 2 + 2 < heap_size && cmp(*root, *r)) root = r;
  if (root != base) {
    std::swap(*base, *root);
    heapify(first, last, root, heap_size, cmp);
  }
}

template <class It, class Compare = std::less<>>
void heap_sort(It first, It last, Compare cmp = Compare{}) {
  size_t heap_size = std::distance(first, last);
  It base = std::next(first, heap_size / 2 - 1);
  for (auto it = base; it != std::prev(first); it--) {
    heapify(first, last, it, heap_size, cmp);
  }
  for (auto it = std::prev(last); it != first; it--) {
    std::swap(*it, *first);
    heapify(first, last, first, --heap_size, cmp);
  }
}

template <class It, class Compare = std::less<>>
It my_partition(It first, It last, Compare cmp = Compare{}) {
  auto axis = *std::prev(last);
  It i = std::prev(first);
  for (auto j = first; j != last; j++) {
    if (cmp(*j, axis)) {
      i++;
      std::swap(*j, *i);
    }
  }
  std::swap(*std::next(i), *std::prev(last));
  return std::next(i);
}

template <class It, class Compare = std::less<>>
void quick_sort(It first, It last, Compare cmp = Compare{}) {
  if (first == last) {
    return;
  } else {
    auto axis = my_partition(first, last, cmp);
    quick_sort(first, axis, cmp);
    quick_sort(std::next(axis), last, cmp);
  }
}

template <class It, class Compare = std::less<>>
void insertion_sort(It first, It last, Compare cmp = Compare{}) {
  It begin = first;
  while (first != last) {
    It temp1 = first;
    while (cmp(*temp1, *std::prev(temp1)) && temp1 != begin) {
      std::swap(*temp1, *std::prev(temp1));
      temp1--;
    }
    first++;
  }
}

#endif  // INCLUDE_SORTING_HPP_
