#pragma once
#include <cmath>
#include <array>

template <typename T> class rosenbrock {
private:
  float a;
  float b;

public:
  rosenbrock(float a, float b) : a(a), b(b){};
  T operator()(std::array<T, 2> x_vec) {
    T x = x_vec[0], y = x_vec[1];
    return std::pow(x - a, 2) + std::pow(y - x * x, 2) * b;
  };
};
