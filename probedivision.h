#ifndef PROBEDIVISION_H
#define PROBEDIVISION_H
#include <gmpxx.h>
#include <list>

class Factor {
public:
  unsigned int exponent;
  mpz_class factor;
  int is_prime;

  Factor();
  void printpp();
};

unsigned int divide_out_maximal_power(mpz_class *t, mpz_class P);
std::list<Factor> trial_division_bounded(mpz_class N, mpz_class B);
std::list<Factor> trial_division(mpz_class N);

#endif
