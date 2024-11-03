#include "Polynomial.h"
#include "Z.h"
#include "Zmod.h"
#include <gmpxx.h>
#include <iostream>

int main() {
  // 1. Beispiel: Zmod<7> mit großen Zahlen

  // Große Koeffizienten für Zmod<7>
  Zmod<7> z1(mpz_class(
      "987654347382107438201432121012345674321432143214321432143214783290174893"
      "021784930271849032718940732891074839201789")); // Modulo 7
  Zmod<7> z2(mpz_class("9999999999999999994738291074839021784930217849032718490"
                       "3728194073289104783920149")); // Modulo 7
  Zmod<7> z3(mpz_class("5555555555555555555"));       // Modulo 7

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
  // std::cout << "Quotient (Zmod<7>): ";
  // quotient_mod7.printAsFunction();
  //
  // std::cout << "Rest (Zmod<7>): ";
  // remainder_mod7.printAsFunction();

  // 2. Beispiel: Z mit großen Zahlen

  // Große Koeffizienten für Z
  Z z1_big(mpz_class("2"));
  Z z2_big(mpz_class("3"));
  Z z3_big(mpz_class("555555555555543214321432143214321432143214321432143210057"
                     "4839105768329016555555"));

  std::vector<Z> coefficients_z1 = {z1_big, z1_big, z1_big, z1_big,
                                    z2_big, z2_big, z2_big, z2_big};
  std::vector<Z> coefficients_z2 = {Z(mpz_class("1")),
                                    Z(mpz_class("1"))}; // p_4(x) = x + 1

  // Polynome erstellen
  Polynomial<Z> poly_z1(coefficients_z1);
  Polynomial<Z> poly_z2(coefficients_z2);

  // Division durchführen
  auto [quotient_z, remainder_z] = poly_z1 / poly_z2;

  // Ausgabe der Resultate für Z
  // std::cout << "Quotient (Z): ";
  // quotient_z.printAsFunction();
  //
  // std::cout << "Rest (Z): ";
  // remainder_z.printAsFunction();
  poly_z1.evalAt(coefficients_z1);
  return 0;
}
