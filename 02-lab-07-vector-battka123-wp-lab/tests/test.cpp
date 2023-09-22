// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <gtest/gtest.h>

#include <algorithm>

#include "vector.hpp"

TEST(VectorTest, Constructors) {
  vector<int> v1;
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);

  vector<int> v2(5);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], 0);
  }

  vector<int> v3(3, 7);
  EXPECT_EQ(v3.size(), 3);
  EXPECT_EQ(v3.capacity(), 3);
  for (size_t i = 0; i < v3.size(); ++i) {
    EXPECT_EQ(v3[i], 7);
  }

  vector<int> v4(v3);
  EXPECT_EQ(v4.size(), v3.size());
  EXPECT_EQ(v4.capacity(), v3.capacity());
  for (size_t i = 0; i < v4.size(); ++i) {
    EXPECT_EQ(v4[i], v3[i]);
  }
}

TEST(VectorTest, AssignmentOperator) {
  vector<int> v3(3, 7);
  vector<int> v5;
  v5 = v3;
  EXPECT_EQ(v5.size(), v3.size());
  EXPECT_EQ(v5.capacity(), v3.capacity());
  for (size_t i = 0; i < v5.size(); ++i) {
    EXPECT_EQ(v5[i], v3[i]);
  }
}

TEST(VectorTest, ElementAccessOperators) {
  vector<int> v6(2, 5);
  EXPECT_EQ(v6[0], 5);
  EXPECT_EQ(v6[1], 5);
  EXPECT_EQ(v6.at(0), 5);
  EXPECT_EQ(v6.at(1), 5);
  EXPECT_EQ(v6.front(), 5);
  EXPECT_EQ(v6.back(), 5);
  v6[0] = 7;
  EXPECT_EQ(v6[0], 7);
}

TEST(VectorTest, Iterators) {
  vector<int> v7(3, 2);
  int sum = 0;
  for (auto it = v7.begin(); it != v7.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(VectorTest, InformationMethods) {
  vector<int> v8;
  EXPECT_TRUE(v8.empty());
  EXPECT_EQ(v8.size(), 0);
  EXPECT_EQ(v8.capacity(), 0);
  v8.reserve(10);
  EXPECT_EQ(v8.capacity(), 10);
  v8.clear();
  EXPECT_TRUE(v8.empty());
  EXPECT_EQ(v8.size(), 0);
  EXPECT_EQ(v8.capacity(), 0);
}

TEST(VectorTest, ModificationMethods) {
  vector<int> v9(2, 3);
  v9.insert(1, 5);
  EXPECT_EQ(v9.size(), 3);
  EXPECT_EQ(v9[0], 3);
  EXPECT_EQ(v9[1], 5);
  EXPECT_EQ(v9[2], 3);
  v9.push_back(7);
  EXPECT_EQ(v9.size(), 4);
  EXPECT_EQ(v9[3], 7);
  v9.pop_back();
  EXPECT_EQ(v9.size(), 3);
  EXPECT_EQ(v9[2], 3);
  vector<int> v10(2, 1);
  v9.swap(v10);
  EXPECT_EQ(v9.size(), 2);
  EXPECT_EQ(v9[0], 1);
  EXPECT_EQ(v9[1], 1);
  EXPECT_EQ(v10.size(), 3);
  EXPECT_EQ(v10[0], 3);
  EXPECT_EQ(v10[1], 5);
  EXPECT_EQ(v10[2], 3);
}

TEST(VectorTest, PushBackTest) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
}

TEST(VectorTest, PopBackTest) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  v.pop_back();

  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
}

TEST(VectorTest, SortSTLTest) {
  vector<int> v;
  v.push_back(3);
  v.push_back(2);
  v.push_back(1);

  std::sort(v.begin(), v.end());

  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
}

TEST(VectorTest, FindIfSTLTest) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  auto it = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });

  ASSERT_EQ(*it, 2);
}

TEST(VectorTest, FindIfTest) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  auto it = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });

  ASSERT_EQ(*it, 2);
}
