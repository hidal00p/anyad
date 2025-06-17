#include "cppunitlite/TestHarness.h"
#include "cppunitlite/TestResultStdErr.h"
#include "dual.hpp"
#include <cmath>

TEST(test_passive_dual_addition) {
  dual a = 2.0;
  dual b = 3.0;

  CHECK((a+b).der == 0.0 && (a+b).val == a.val + b.val);
}

TEST(test_active_dual_addition) {
  dual a = dual::active(2.0);
  dual b = 3.0;

  CHECK((a+b).der == 1.0);
}

TEST(test_passive_dual_product) {
  dual a = 2.0;
  dual b = 3.0;

  CHECK((a*b).der == 0.0 && (a*b).val == a.val * b.val);
}

TEST(test_active_dual_product) {
  dual a = dual::active(2.0);
  dual b = 3.0;

  CHECK((a*b).der == b.val);
}

TEST(test_overloaded_sin) {
  dual a = dual::active(2.0);
  dual f = std::sin(a);

  CHECK(f.der == std::cos(a.val) && f.val == std::sin(a.val));
}

TEST(test_overloaded_cos) {
  dual a = dual::active(2.0);
  dual f = std::cos(a);

  CHECK(f.der == -std::sin(a.val) && f.val == std::cos(a.val));
}

TEST(test_overloaded_exp) {
  dual a = dual::active(2.0);
  dual f = std::exp(a);

  double f_regular = std::exp(a.val);
  CHECK(f.der == f_regular && f.val == f_regular);
}

int main() {
  TestResultStdErr result;
  TestRegistry::runAllTests(result);
  return (result.getFailureCount());
}
