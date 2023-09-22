// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <gtest/gtest.h>

#include <polynomial.hpp>

TEST(Polynomial, Init) {
  const std::vector<int> pol = {1, 6, 3};
  const Polynomial p(pol);
  EXPECT_EQ(p.Coeff(0), 1);
  EXPECT_EQ(p.Coeff(1), 6);
  EXPECT_EQ(p.Coeff(2), 3);
}

TEST(Polynomial, CopyAssign) {
  const std::vector<int> pol = {6, 2, 4};
  const Polynomial p(pol);
  Polynomial c(p);
  EXPECT_EQ(p, c);
  c = p;
  EXPECT_EQ(p, c);
}

TEST(Polinomial, AddPolinom) {
  const std::vector<int> pol = {1, 1, 1};
  Polynomial p(pol);
  const std::vector<int> pol_add = {2, 3, 4};
  const Polynomial p_add(pol_add);
  p += p_add;
  EXPECT_EQ(p.Coeff(0), 3);
  EXPECT_EQ(p.Coeff(1), 4);
  EXPECT_EQ(p.Coeff(2), 5);
  p = p + p_add;
  EXPECT_EQ(p.Coeff(0), 5);
  EXPECT_EQ(p.Coeff(1), 7);
  EXPECT_EQ(p.Coeff(2), 9);
}
TEST(Polynomial, SubPolinom) {
  const std::vector<int> pol = {9, 7, 5};
  Polynomial p(pol);
  const std::vector<int> pol_sub = {4, 3, 2};
  const Polynomial p_sub(pol_sub);
  p -= p_sub;
  EXPECT_EQ(p.Coeff(0), 5);
  EXPECT_EQ(p.Coeff(1), 4);
  EXPECT_EQ(p.Coeff(2), 3);
  p = p - p_sub;
  EXPECT_EQ(p.Coeff(0), 1);
  EXPECT_EQ(p.Coeff(1), 1);
  EXPECT_EQ(p.Coeff(2), 1);
}

TEST(Polinomial, MultPolinom) {
  const std::vector<int> pol = {2, 3, 4};
  Polynomial p(pol);
  const std::vector<int> pol_sub = {40, 30, 20};
  const Polynomial p_sub(pol_sub);
  p *= p_sub;
  // 80
  // 60+120 = 180
  // 40+90+160 = 290
  // 60+120 = 180
  // 80
  EXPECT_EQ(p.Coeff(0), 80);
  EXPECT_EQ(p.Coeff(1), 180);
  EXPECT_EQ(p.Coeff(2), 290);
  EXPECT_EQ(p.Coeff(3), 180);
  EXPECT_EQ(p.Coeff(4), 80);
  /*
  Polynomial p_2(pol);
  p_2 = p_2 * p_sub;
  EXPECT_EQ(p, p_2);
  */
}
TEST(Polinom, MultConst) {
  const std::vector<int> pol = {2, 3, 4};
  Polynomial p(pol);
  p *= 10;
  EXPECT_EQ(p.Coeff(0), 20);
  EXPECT_EQ(p.Coeff(1), 30);
  EXPECT_EQ(p.Coeff(2), 40);
  p = p * 7;
  EXPECT_EQ(p.Coeff(0), 140);
  EXPECT_EQ(p.Coeff(1), 210);
  EXPECT_EQ(p.Coeff(2), 280);
}
TEST(Polinomial, Degree) {
  const std::vector<int> pol = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  Polynomial p(pol);
  EXPECT_EQ(p.Degree(), 11);

  const std::vector<int> pol_2 = {1, 2, 3, 4, 11, 12};
  Polynomial p_2(pol_2);
  EXPECT_EQ(p_2.Degree(), 5);
}

TEST(Polinomial, DivPolinom) {
  const std::vector<int> pol = {100, 200, 300};
  Polynomial p(pol);
  const std::vector<int> pol_2 = {25, 20};
  const Polynomial p_2(pol_2);
  p /= p_2;
  EXPECT_EQ(p.Coeff(0), 4);
  EXPECT_EQ(p.Coeff(1), 4);
  EXPECT_EQ(p.Coeff(2), 0);
  p = p / p_2;
  EXPECT_EQ(p.Coeff(0), 0);
  EXPECT_EQ(p.Coeff(1), 0);
  EXPECT_EQ(p.Coeff(2), 0);
}

TEST(Polinomial, ModPolinom) {
  const std::vector<int> pol = {1054, 2540, 840};
  Polynomial p(pol);
  const std::vector<int> pol_2 = {23, 13};
  const Polynomial p_2(pol_2);
  p %= p_2;
  EXPECT_EQ(p.Coeff(0), 19);
  EXPECT_EQ(p.Coeff(1), 16);
  EXPECT_EQ(p.Coeff(2), 0);
  p = p % p_2;
  EXPECT_EQ(p.Coeff(0), 19);
  EXPECT_EQ(p.Coeff(1), 0);
  EXPECT_EQ(p.Coeff(2), 0);
}

TEST(Polinomial, SetCoeff) {
  const std::vector<int> pol = {105, 207, 309};
  Polynomial p(pol);
  p.SetCoeff(2, 144);
  EXPECT_EQ(p.Coeff(2), 144);
}
TEST(Polinolial, Count) {
  const std::vector<int> pol = {5, 10, 8};
  Polynomial p(pol);
  EXPECT_EQ(p(1), 23);
  const std::vector<int> pol2 = {2, 3, 4};
  Polynomial p2(pol2);
  EXPECT_EQ(p2(2), 24);
}
