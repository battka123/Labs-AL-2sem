// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <gtest/gtest.h>

#include <sorting.hpp>
#include <fstream>
#include <thread>

TEST(Merge_Out, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  merge_sort(array_u.begin(), array_u.end(), array_u.begin(), std::less());
  EXPECT_EQ(array_u, array_s);
}

TEST(Merge_Inplace, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  inplace_merge_sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
TEST(Insertion, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  insertion_sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
TEST(Quick, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  quick_sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
TEST(Heap, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  heap_sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
TEST(Stable, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  std::stable_sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
TEST(Sort, Sort) {
  std::vector<int> array_u, array_s;
  std::ifstream in("../tests/unsorted.txt"), in1("../tests/sorted.txt");
  int x, y;
  if (!in || !in1) {
    std::cout << "closed";
    return;
  }
  while (in >> x && in1 >> y) {
    array_u.push_back(x);
    array_s.push_back(y);
  }
  in.close();
  in1.close();
  std::sort(array_u.begin(), array_u.end(), std::less());
  EXPECT_EQ(array_u, array_s);
}
