#pragma once
#include <string>

class dual {
public:
  double val;
  double der;

  dual(double val, double der = 0.0) : val(val), der(der){};

  static dual active(double val);
  static dual passive(double val);

  std::string to_str();

  dual operator+(dual other);
  dual operator-(dual other);
  dual operator*(dual other);
};

namespace std {
dual sin(dual x);
dual cos(dual x);
dual exp(dual x);
dual pow(dual x, int n);
} // namespace std
