#include "Polynomial.h"
#include "Z.h"
#include "Zmod.h"
#include <gmpxx.h>
#include <iostream>

int main() {
  Zmod<7> z1 = Zmod<7>(5);
  Zmod<7> z2 = Zmod<7>(5);
  Zmod<7> z3 = z1 * z2;

  Z z(5);

  // std::cout << z3.getOriginalValue() << std::endl;
  // std::cout << z.getValue() << std::endl;
  // std::cout << z.invert() << std::endl;

  std::vector<Z> coefficients1 = {Z(1), Z(2), Z(3)};
  std::vector<Zmod<7>> coefficients2 = {z1, z1, z1};

  Polynomial<Zmod<7>> poly1(coefficients2);
  Polynomial<Zmod<7>> poly2(coefficients2);

  auto [q, r] = poly1 / poly2;
  q.printAsFunction();
  r.printAsSequence();
  return 0;
}
