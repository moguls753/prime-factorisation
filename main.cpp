#include "Polynomial.h"
#include "Z.h"
#include "Zmod.h"
#include <gmpxx.h>
#include <iostream>

int main() {
  Z z1_big(mpz_class("2"));
  Z z2_big(mpz_class("3"));

  std::vector<Z> coefficients_z1 = {
      z1_big, z1_big, z1_big, z1_big, z1_big, z1_big, z1_big, z1_big,
      z1_big, z1_big, z1_big, z1_big, z2_big, z2_big, z2_big, z2_big};
  std::vector<Z> coefficients_z2 = {Z(mpz_class("1")),
                                    Z(mpz_class("1"))}; // p_4(x) = x + 1

  Polynomial<Z> poly_z1(coefficients_z1);
  Polynomial<Z> poly_z2(coefficients_z2);
  std::vector<Z> vector_a = {mpz_class(5), mpz_class(1), mpz_class(0),
                             mpz_class(2), mpz_class(3)};
  std::vector<Z> vector_b = {mpz_class(3), mpz_class(2), mpz_class(1)};
  Polynomial<Z> a(vector_a);
  Polynomial<Z> b(vector_b);
  std::vector<Z> results = poly_z1.evalAt(std::vector<Z>(
      {mpz_class("2"), mpz_class("2"), mpz_class("2"), mpz_class("2"),
       mpz_class("2"), mpz_class("2"), mpz_class("2"), mpz_class("2"),
       mpz_class("3"), mpz_class("3"), mpz_class("3"), mpz_class("3"),
       mpz_class("3"), mpz_class("3"), mpz_class("3"), mpz_class("3")}));
  // for (Z i : results) {
  //   std::cout << i.getValue() << ' ';
  // }
  poly_z1.printAsFunction();
  // std::vector<Z> test = poly_z1.evalAt(coefficients_z1);
  // for (Z i : test) {
  //   std::cout << i.getValue() << ' ';
  // }
  return 0;
}
