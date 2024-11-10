/* Datei "probedivision.cpp" enthält ein Programm zur Faktorisierung von Zahlen
mittels Probedivision Kompilieren: g++ probedivision.cpp testzahlen.cpp -lgmp
-lgmpxx Ausführen mit Parameter: -F = Fermatzahl F_k -C = Cunninghamzahl
(1111...111) -B = Testzahl b_k -R = RSA-Zahl R_k ohne Parameter: freie Eingabe
einer Zahl.

 (Beispielprogramm von Steffen Kionke für das Praktikum Algebra 2022)
 */

#include "probedivision.h"
#include <iostream>

/*
 Klasse "Factor": Kann genutzt werden um einen (Prim)Faktor mit Exponenten zu
 speichern.
 */
Factor::Factor() {
  exponent = 0;
  is_prime = 0;
  factor = mpz_class("1");
}

void Factor::printpp() {
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
  while (tmp > 1 && P <= B) {
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
