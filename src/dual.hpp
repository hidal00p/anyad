#pragma once
#include <string>

/**
 * A data type that implements a dual floating-point
 * arithmetic. The term "dual" means that the derivatve
 * computation is performed alongside the original computation.
 *
 * Mathematically this is possible because of the chain rule
 * of differentiation.
 *
 * The dual class contains two fields - val and der.
 * Computations done on the val filed are the same as the
 * computations that would have been done on a regular real-valued
 * variable. Computations done on the der field are the dual
 * derivative computations.
 *
 * Usage:
 *
 * // Declare a variable wrt to which the derivative is desired
 * dual x = dual::active(42.0);
 *
 * // Due to the overloaded * operator, the derivative is also computed as
 * // 2 * x, and is stored in the der filed of the f variable.
 * dual f = x * x;
 *
 * // Prints 84.0 or df/dx = 2 * x = 2 * 42 = 84.
 * std::cout << f.der << std::endl;
 */
class dual {
public:
  double val;
  double der;

  dual(double val, double der = 0.0) : val(val), der(der){};

  /**
   * A factory method that instantiates an acive value, derivatives
   * with respect to which will be propagated.
   *
   * @param val - a regular value of a variable
   * @return dual, which can be used to propagate derivatives
   */
  static dual active(double val);

  /**
   * A factory method that instantiates a passive value, derivatives
   * with respect to which will NOT be propagated.
   */
  static dual passive(double val);

  std::string to_str();

  /**
   * Add two FP values in a dual manner
   *
   * c = a + b
   * dc = da + db
   */
  dual operator+(dual other);

  /**
   * Subtract two FP values in a dual manner
   *
   * c = a - b
   * dc = da - db
   */
  dual operator-(dual other);

  /**
   * Multiply two FP values in a dual manner
   *
   * c = a * b
   * dc = b*da + a*db
   */
  dual operator*(dual other);
};

/**
 * Some standard mathematics functions overloaded for the dual
 * computation with the dual data type.
 */
namespace std {
dual sin(dual x);
dual cos(dual x);
dual exp(dual x);
dual pow(dual x, int n);
} // namespace std
