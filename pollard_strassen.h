#ifndef POLLARD_STRASSEN_H
#define POLLARD_STRASSEN_H
#include <gmpxx.h>
#include <vector>

mpz_class pollardStrassen(const mpz_class N, const mpz_class b);

std::vector<mpz_class> primeFactorisation(mpz_class N, const mpz_class b);

#endif
