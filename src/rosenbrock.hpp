#pragma once
#include <array>
#include <cmath>

/**
 * Rosenbrock function - https://en.wikipedia.org/wiki/Rosenbrock_function.
 */
template <typename T = double> class rosenbrock {
private:
  float a;
  float b;

public:
  /**
   * @param a - a function parameter, from which the extremum point can be
   * inferred.
   * @param b - a function parameter, from which the difficulty to obtain the
   * extremum can be inferred.
   */
  rosenbrock(float a, float b) : a(a), b(b){};

  /**
   * An overloaded () operator to evaluate the function at a pair of points
   * (x_0, x_1).
   * @param x_vec - a 2D argument at which the function is evaluated
   * @return the result of the evaluation
   */
  T operator()(std::array<T, 2> x_vec) {
    T x = x_vec[0], y = x_vec[1];
    return std::pow(x - a, 2) + std::pow(y - x * x, 2) * b;
  };
};
