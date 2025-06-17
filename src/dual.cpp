#include "dual.hpp"
#include <cmath>

dual dual::active(double val) { return dual(val, 1.0); }
dual dual::passive(double val) { return dual(val); }

std::string dual::to_str() {
  return "val: " + std::to_string(val) + "\nder: " + std::to_string(der);
}

dual dual::operator+(dual other) {
  return dual(val + other.val, der + other.der);
}

dual dual::operator-(dual other) {
  return dual(val - other.val, der - other.der);
}

dual dual::operator*(dual other) {
  return dual(val * other.val, other.val * der + val * other.der);
}

namespace std {
dual sin(dual x) { return dual(std::sin(x.val), std::cos(x.val) * x.der); };

dual cos(dual x) { return dual(std::cos(x.val), -std::sin(x.val) * x.der); };

dual exp(dual x) { return dual(std::exp(x.val), std::exp(x.val) * x.der); };

dual pow(dual x, int n) {
  return dual(std::pow(x.val, n), n * std::pow(x.val, n - 1) * x.der);
};
} // namespace std
