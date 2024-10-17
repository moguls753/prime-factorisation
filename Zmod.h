#ifndef ZMOD_H
#define ZMOD_H

#include "Ring.h"

template <int Modulus> class Zmod : public Ring<Zmod<Modulus>> {
public:
  Zmod();
  Zmod(const mpz_class &value);
  mpz_class reducedValue() const;
  Zmod operator+(const Zmod &other) const override;
  Zmod operator*(const Zmod &other) const override;
  Zmod abs() const override;
  bool operator!=(const Zmod &other) const override;
  bool operator<(const Zmod &other) const override;
  bool operator>(const Zmod &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;

  static Zmod one();
  static Zmod zero();
};

#endif
