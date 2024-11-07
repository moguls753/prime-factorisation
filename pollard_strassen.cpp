#include "polynomial.h"

mpz_class pollardStrassen(const mpz_class N, mpz_class b) {
  mpz_class c;
  mpz_class remainder;
  mpz_sqrtrem(c.get_mpz_t(), remainder.get_mpz_t(), b.get_mpz_t());
  // Laut Paper wird die wirkliche Wurzel aufgerundet, also wird c erst später
  // c+1 zugewiesen als hier.
  c = (remainder == 0) ? (c + 1) : c;
  std::vector<Zmod> points;
  for (Zmod j = Zmod(1, N); j.getValue() <= c; j + j) {
    points.push_back(j);
  }
  Polynomial<Zmod> poly(points);
  std::vector<Polynomial<Zmod>> tree = poly.buildSubproductTree(points);
  for (const auto &i : tree) {
    i.printAsSequence();
    std::cout << "/n";
  }
  return 0;
}
