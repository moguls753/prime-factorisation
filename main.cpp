#include "Polynomial.h"
#include "Z.h"
#include "Zmod.h"
#include <gmpxx.h>
#include <iostream>

int main() {
  // 1. Beispiel: Zmod<7> mit großen Zahlen

  // Große Koeffizienten für Zmod<7>
  Zmod<7> z1(mpz_class("9876543210123456789")); // Modulo 7
  Zmod<7> z2(mpz_class("9999999999999999999")); // Modulo 7
  Zmod<7> z3(mpz_class("5555555555555555555")); // Modulo 7

  std::vector<Zmod<7>> coefficients1 = {z3, z2,
                                        z1}; // p_1(x) = z1*x^2 + z2*x + z3
  std::vector<Zmod<7>> coefficients2 = {Zmod<7>(1),
                                        Zmod<7>(1)}; // p_2(x) = x + 1

  // Polynome erstellen
  Polynomial<Zmod<7>> poly1(coefficients1);
  Polynomial<Zmod<7>> poly2(coefficients2);

  // Division durchführen
  auto [quotient_mod7, remainder_mod7] = poly1 / poly2;

  // Ausgabe der Resultate für Zmod<7>
  std::cout << "Quotient (Zmod<7>): ";
  quotient_mod7.printAsFunction();

  std::cout << "Rest (Zmod<7>): ";
  remainder_mod7.printAsFunction();

  // 2. Beispiel: Z mit großen Zahlen

  // Große Koeffizienten für Z
  Z z1_big(mpz_class("9876543210123456789"));
  Z z2_big(mpz_class("9999999999999999999"));
  Z z3_big(mpz_class("5555555555555555555"));

  std::vector<Z> coefficients_z1 = {z3_big, z2_big,
                                    z1_big}; // p_3(x) = z1*x^2 + z2*x + z3
  std::vector<Z> coefficients_z2 = {Z(mpz_class("1")),
                                    Z(mpz_class("1"))}; // p_4(x) = x + 1

  // Polynome erstellen
  Polynomial<Z> poly_z1(coefficients_z1);
  Polynomial<Z> poly_z2(coefficients_z2);

  // Division durchführen
  auto [quotient_z, remainder_z] = poly_z1 / poly_z2;

  // Ausgabe der Resultate für Z
  std::cout << "Quotient (Z): ";
  quotient_z.printAsFunction();

  std::cout << "Rest (Z): ";
  remainder_z.printAsFunction();

  return 0;
}
