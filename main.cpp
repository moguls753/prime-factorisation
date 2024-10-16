#include "Polynomial.h"
#include "Z.h"
#include "Zmod.h"
#include <gmpxx.h>
#include <iostream>

int main() {
  Zmod z1(5, 7);
  Zmod z2(5, 7);
  Zmod z3 = z1 * z2;

  Z z(5);

  std::cout << z3.reducedValue() << std::endl;
  std::cout << z.getValue() << std::endl;

  std::vector<Z> coefficients1 = {Z(1), Z(2), Z(3)};
  std::vector<Z> coefficients2 = {z, z, z};

  Polynomial<Z> poly1(coefficients1);
  Polynomial<Z> poly2(coefficients2);

  Polynomial<Z> poly3 = poly1 + poly2;

  poly3.printAsSequence();

  poly3 = poly1 * poly2;

  poly3.printAsFunction();
  poly3.printAsSequence();
  return 0;
}
