#include "polynomial.h"
#include "z_mod.h"

mpz_class pollardStrassen(const mpz_class N, mpz_class b) {

  // Schritt 1 und 2
  mpz_class c;
  mpz_class remainder;
  mpz_sqrtrem(c.get_mpz_t(), remainder.get_mpz_t(), b.get_mpz_t());
  // Laut Paper wird die wirkliche Wurzel aufgerundet, also wird c erst später
  // c+1 zugewiesen als hier.
  c = (remainder != 0) ? (c + 1) : c;
  std::vector<Zmod> points;
  for (Zmod j = Zmod(1, N); j.getValue() <= c; j = j + Zmod(1, N)) {
    points.push_back(j);
  }
  Polynomial<Zmod> poly(points);
  std::vector<Zmod> ic_points;
  for (Zmod i = Zmod(0, N); i.getValue() <= c; i = i + Zmod(1, N)) {
    ic_points.push_back(i * Zmod(c, N));
  }
  std::vector<Zmod> result = poly.evalAt(ic_points);
  for (const auto &i : result) {
    std::cout << i << ' ';
  }
  poly.printAsSequence();

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

  return mpz_class(result[k].getValue());
}
