// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <gtest/gtest.h>

#include "circuits.hpp"

TEST(ElementTest, ResistorTest) {
  float resistance = 100.0f;
  Resistor r(resistance);
  Power p(50.0f);
  EXPECT_FLOAT_EQ(r.CalculateResistance(p), resistance);
}

TEST(ElementTest, CapacitorTest) {
  float capacitance = 1.0e-6f;
  Capacitor c(capacitance);
  Power p(50.0f);
  float expected_impedance =
      -1.0f / (p.Frequency() * 2.0f * M_PI * capacitance);
  float expected_resistance = std::abs(expected_impedance);
  EXPECT_FLOAT_EQ(c.CalculateResistance(p), expected_resistance);
}

TEST(ElementTest, InductorTest) {
  float inductance = 50.0e-3f;
  Inductor l(inductance);
  Power p(50.0f);
  float expected_impedance = p.Frequency() * 2.0f * M_PI * inductance;
  float expected_resistance = std::abs(expected_impedance);
  EXPECT_FLOAT_EQ(l.CalculateResistance(p), expected_resistance);
}

TEST(ElementTest, ParallelConnectionsTest) {
  float resistance1 = 100.0f;
  float resistance2 = 200.0f;
  Resistor r1(resistance1);
  Resistor r2(resistance2);
  ParallelConnections pc;
  pc.AddElement(&r1);
  pc.AddElement(&r2);

  Power p(50.0f);

  float expected_resistance = 1.0f / (1.0f / resistance1 + 1.0f / resistance2);
  float expected_conductance = 1.0f / expected_resistance;

  float expected_impedance = -1.0f / (p.Frequency() * 2.0f * M_PI);
  expected_impedance += expected_conductance;
  expected_impedance += 1.0f / expected_resistance;

  EXPECT_FLOAT_EQ(pc.CalculateResistance(p), std::abs(expected_impedance));
}

TEST(ElementTest, SequentialConnectionsTest) {
  float resistance1 = 100.0f;
  float resistance2 = 200.0f;
  Resistor r1(resistance1);
  Resistor r2(resistance2);
  SequentialConnections sc;
  sc.AddElement(&r1);
  sc.AddElement(&r2);

  Power p(50.0f);

  float expected_resistance = resistance1 + resistance2;

  EXPECT_FLOAT_EQ(sc.CalculateResistance(p), expected_resistance);
}
