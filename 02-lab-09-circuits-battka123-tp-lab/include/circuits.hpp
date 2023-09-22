// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_CIRCUITS_HPP_
#define INCLUDE_CIRCUITS_HPP_

#include <cmath>
#include <vector>

class Power {
 private:
  float frequency_;

 public:
  explicit Power(float frequency) : frequency_(frequency) {}
  [[nodiscard]] float Frequency() const { return frequency_; }
};

class Element {
 public:
  virtual ~Element() = default;
  [[nodiscard]] virtual float CalculateResistance(const Power&) const = 0;
};

class Resistor : public Element {
 private:
  float resistance_;

 public:
  explicit Resistor(float resistance) : resistance_(resistance) {}

  [[nodiscard]] float CalculateResistance(const Power&) const override {
    return resistance_;
  }
};

class Capacitor : public Element {
 private:
  float capacitance_;

 public:
  explicit Capacitor(float capacitance) : capacitance_(capacitance) {}

  [[nodiscard]] float CalculateResistance(const Power& power) const override {
    float impedance = -1.0f / (power.Frequency() * 2.0f * M_PI * capacitance_);
    return std::abs(impedance);
  }
};

class Inductor : public Element {
 private:
  float inductance_;

 public:
  explicit Inductor(float inductance) : inductance_(inductance) {}

  [[nodiscard]] float CalculateResistance(const Power& power) const override {
    float impedance = power.Frequency() * 2.0f * M_PI * inductance_;
    return std::abs(impedance);
  }
};

class ParallelConnections : public Element {
 private:
  std::vector<Element*> elements_;

 public:
  void AddElement(Element* element) { elements_.push_back(element); }

  [[nodiscard]] float CalculateResistance(const Power& power) const override {
    float resistance_sum = 0.0f;
    float conductance_sum = 0.0f;
    for (const auto& element : elements_) {
      float element_resistance = element->CalculateResistance(power);
      resistance_sum += 1.0f / element_resistance;
      conductance_sum += 1.0f / element_resistance;
    }
    float equivalent_resistance = 1.0f / resistance_sum;
    float equivalent_conductance = conductance_sum;
    float impedance = -1.0f / (power.Frequency() * 2.0f * M_PI);
    impedance += equivalent_conductance;
    impedance += 1.0f / equivalent_resistance;
    return std::abs(impedance);
  }
};

class SequentialConnections : public Element {
 private:
  std::vector<Element*> elements_;

 public:
  void AddElement(Element* element) { elements_.push_back(element); }

  [[nodiscard]] float CalculateResistance(const Power& power) const override {
    float resistance_sum = 0.0f;
    for (const auto& element : elements_) {
      float element_resistance = element->CalculateResistance(power);
      resistance_sum += element_resistance;
    }
    return resistance_sum;
  }
};

#endif  // INCLUDE_CIRCUITS_HPP_
