#include "polynomial.h"
#include "z_mod.h"

mpz_class pollardStrassen(const mpz_class N, mpz_class b) {
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
  std::cout << "FME: ";
  for (const auto &i : result) {
    std::cout << i.getValue() << " ";
  }
  return 0;
}
