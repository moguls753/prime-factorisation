#include "pollard_strassen.h"
#include "polynomial.h"
#include "testzahlen.h"
#include "z.h"
#include "z_mod.h"
#include <chrono>
#include <gmpxx.h>
#include <iostream>
#include <list>

class Factor {
public:
  unsigned int
      exponent; // Exponent: erlaubt es Faktoren mit Potenzen zu zählen (2^6)
  mpz_class factor; // Faktor (im besten Fall: eine Primzahl)
  int is_prime;     // Ist "factor" eine Primzahl? 2 sicher, 1 wahrscheinlich, 0
                    // nein
  Factor() {
    exponent = 0;
    is_prime = 0;
    factor = mpz_class("1");
  }
  void printpp() {
    char open = '(';
    char close = ')';

    if (is_prime == 0) // Faktor ist nicht prim
    {
      open = '[';
      close = ']';
    }

    std::cout << open << factor;

    if (exponent > 1)
      std::cout << "^" << exponent;
    if (is_prime == 1) // nicht 100% sicher prim
      std::cout << "_?";

    std::cout << close << " ";
  }
};

/*
 divide_out_maximal_power takes a number T and a (prime) number P returns
 maximal exponent e such that P^e divides T. In the end T is T/P^e.
 */
unsigned int divide_out_maximal_power(mpz_class *t, mpz_class P) {
  unsigned int exponent = 0;
  while ((*t) % P == 0) {
    *t = (*t) / P;
    exponent++;
  }
  return exponent;
}
/*
 Faktorisiert die Zahl N mittels Probedivision bis zur Schranke B und prüft, ob
 der Rest eine Primzahl ist. Gibt die Liste der gefundenen Primfaktoren zurück.
 (Für große Zahlen N muss eine sinnvolle Schranke B gewählt werden, sonst
 explodiert die Laufzeit!)
*/
std::list<Factor> trial_division_bounded(mpz_class N, mpz_class B) {
  mpz_class tmp = N;
  mpz_class C = sqrt(N) + 1;
  if (B > C)
    B = C;

  std::list<Factor> factors;
  Factor ppt;

  // Prüfen: Ist N eine Primzahl (27: 1 Baille-PSW und 2 Rabin-Müller Tests)
  int a = mpz_probab_prime_p(N.get_mpz_t(), 27);
  if (a > 0) // N ist wahrscheinlich prim
  {
    ppt.exponent = 1;
    ppt.factor = N;
    ppt.is_prime = a;
    factors.push_back(ppt);
    return factors;
  }

  // Andernfalls: Faktorisiere N mit Probedivision
  // Erst 2 und 3, dann alle Zahlen kongruent 1 oder 5 modulo 6
  mpz_class P("2");
  ppt.exponent = divide_out_maximal_power(&tmp, P);
  if (ppt.exponent > 0) {
    ppt.factor = P;
    ppt.is_prime = 2;
    factors.push_back(ppt);
  }
  P++; // P = 3
  ppt.exponent = divide_out_maximal_power(&tmp, P);
  if (ppt.exponent > 0) {
    ppt.factor = P;
    ppt.is_prime = 2;
    factors.push_back(ppt);
  }

  P += 3; // P = 6
  while (tmp > 1 and P <= B) {
    ppt.exponent = divide_out_maximal_power(&tmp, P - 1);
    if (ppt.exponent > 0) {
      ppt.factor = P - 1;
      ppt.is_prime = 2;
      factors.push_back(ppt);
    }
    ppt.exponent = divide_out_maximal_power(&tmp, P + 1);
    if (ppt.exponent > 0) {
      ppt.factor = P + 1;
      ppt.is_prime = 2;
      factors.push_back(ppt);
    }
    P += 6;
  }

  // Prüfen, ob der Rest eine Primzahl ist.
  a = mpz_probab_prime_p(tmp.get_mpz_t(), 27);
  if (tmp > 1) // tmp is probably prime
  {
    ppt.exponent = 1;
    ppt.factor = tmp;
    ppt.is_prime = a;
    factors.push_back(ppt);
    return factors;
  }

  return factors;
}
/*
 Faktorisiert die Zahl N vollständig mittels Probedivision und gibt die Liste
 der Primfaktoren zurück. (Nur für kleine Zahlen (etwa 10^15) funktioniert das
 sicher in annehmbarer Zeit)
 */
std::list<Factor> trial_division(mpz_class N) {
  return trial_division_bounded(N, N);
}

int main() {
  // Z z1_big(mpz_class("2"));
  // Z z2_big(mpz_class("3"));
  //
  // std::vector<Z> coefficients_z1 = {
  //     z1_big, z1_big, z1_big, z1_big, z1_big, z1_big, z1_big, z1_big,
  //     z1_big, z1_big, z1_big, z1_big, z2_big, z2_big, z2_big, z2_big};
  // std::vector<Z> coefficients_z2 = {Z(mpz_class("1")),
  //                                   Z(mpz_class("1"))}; // p_4(x) = x + 1
  //
  // Polynomial<Z> poly_z1(coefficients_z1);
  // Polynomial<Z> poly_z2(coefficients_z2);
  // std::vector<Z> vector_a = {mpz_class(5), mpz_class(1), mpz_class(0),
  //                            mpz_class(2), mpz_class(3)};
  // std::vector<Z> vector_b = {mpz_class(3), mpz_class(2), mpz_class(1)};
  // Polynomial<Z> a(vector_a);
  // Polynomial<Z> b(vector_b);
  // std::vector<Z> results = poly_z1.evalAt(std::vector<Z>(
  //     {mpz_class("2"), mpz_class("2"), mpz_class("2"), mpz_class("2"),
  //      mpz_class("2"), mpz_class("2"), mpz_class("2"), mpz_class("2"),
  //      mpz_class("3"), mpz_class("3"), mpz_class("3"), mpz_class("3"),
  //      mpz_class("3"), mpz_class("3"), mpz_class("3"), mpz_class("3")}));
  // for (Z i : results) {
  //   std::cout << i.getValue() << ' ';
  // }
  // poly_z1.printAsFunction();
  // std::vector<Z> test = poly_z1.evalAt(coefficients_z1);
  // for (Z i : test) {
  //   std::cout << i.getValue() << ' ';
  // }

  for (int i = 1; i <= 10; i++) {
    mpz_class N = mpz_class("43214321432432166");
    mpz_class B("9311321");

    // Zeitmessung starten---------
    std::chrono::time_point<std::chrono::high_resolution_clock> start =
        std::chrono::high_resolution_clock::now();

    std::vector<mpz_class> factors = primeFactorisation(N, B);

    // Zeitmessung stoppen----------
    std::chrono::time_point<std::chrono::high_resolution_clock> end =
        std::chrono::high_resolution_clock::now();

    // Vergangene Zeitspanne bestimmen und ausgeben
    std::chrono::duration<double, std::milli> float_pollard_ms = end - start;
    std::cout << "\nPollard Strassen Verfahre...\n";
    std::cout << "Berechnung in " << float_pollard_ms.count()
              << " Millisekunden abgeschlossen" << std::endl;

    std::cout << "Ermittelte Zerlegung von " << N << ":\n";

    // for (auto &i : factors) {
    //   std::cout << i << " ";
    // }

    std::cout << "\n";

    // Schranke: Probedivision bis 10^8
    // Kann erhöht werden, die Laufzeit wird aber schnell zu groß

    // Zeitmessung starten---------
    start = std::chrono::high_resolution_clock::now();

    // Probedivision durchführen
    std::list<Factor> factors2 = trial_division_bounded(N, B);

    // Zeitmessung stoppen----------
    end = std::chrono::high_resolution_clock::now();
    // Vergangene Zeitspanne bestimmen und ausgeben
    std::chrono::duration<double, std::milli> float_probedivision_ms =
        end - start;
    std::cout << "\nProbedivision...\n";
    std::cout << "Berechnung in " << float_probedivision_ms.count()
              << " Millisekunden abgeschlossen" << std::endl;

    std::cout << "Ermittelte Zerlegung von " << N << ":\n";

    std::list<Factor>::iterator it;
    for (it = factors2.begin(); it != factors2.end(); it++)
      it->printpp();
    std::cout << "\n";
  }

  return 0;
}
