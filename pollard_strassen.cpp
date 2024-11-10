#include "polynomial.h"
#include "z_mod.h"

// gibt 0 zurück wenn failure
mpz_class pollardStrassen(const mpz_class N, mpz_class b) {

  // Schritt 1 und 2
  mpz_class c;
  mpz_class remainder;
  mpz_sqrtrem(c.get_mpz_t(), remainder.get_mpz_t(), b.get_mpz_t());
  // Laut Paper wird die wirkliche Wurzel aufgerundet, also wird c erst später
  // c+1 zugewiesen als hier.
  c = (remainder != 0) ? (c + 1) : c;
  std::vector<Zmod> points;
  mpz_class reserveAmount = c - 2;
  points.reserve(reserveAmount.get_ui());
  for (mpz_class j = 1; j <= c; j++) {
    points.push_back(Zmod(j, N));
  }
  Polynomial<Zmod> f = Polynomial<Zmod>::buildPolynomial(points);
  std::vector<Zmod> ic_points;
  ic_points.reserve(c.get_ui());
  for (mpz_class i = 0; i < c; i++) {
    ic_points.push_back(Zmod(c * i, N));
  }
  std::vector<Zmod> result = f.evalAt(ic_points);

  // Schritt 3
  int k = -1;
  for (int i = 0; i < c; i++) {
    if (gcd(result[i].getValue(), N) > 1) {
      k = i;
      break;
    }
  }

  // keinen nicht trivialen Teiler gefunden
  if (k == -1)
    return mpz_class(0);

  mpz_class d = 0;
  for (int i = 1; i <= c; i++) {
    if (N % (k * c + i) == 0) {
      d = k * c + i;
      // std::cout << d << " ";
      if (d > 1)
        break;
    }
  }

  return mpz_class(d);
}

std::vector<mpz_class> primeFactorisation(mpz_class N, mpz_class b) {
  std::vector<mpz_class> factors;

  while (N > 1) {
    mpz_class factor = pollardStrassen(N, b);

    if (factor == 0) {
      // Ist N selbst prim?
      factors.push_back(N);
      break;
    }

    // falls der Faktor öfter vorkommt
    while (N % factor == 0) {
      factors.push_back(factor);
      N /= factor;
    }
  }

  return factors;
}
