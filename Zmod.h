#ifndef ZMOD_H
#define ZMOD_H

#include "Ring.h"

template <int Modulus> class Zmod : public Ring<Zmod<Modulus>> {
private:
  mpz_class originalValue;

public:
  Zmod();
  Zmod(const mpz_class &value);
  mpz_class originalValue() const;
  Zmod<Modulus> operator+(const Zmod<Modulus> &other) const override;
  Zmod<Modulus> operator*(const Zmod<Modulus> &other) const override;
  Zmod<Modulus> abs() const override;
  bool operator!=(const Zmod<Modulus> &other) const override;
  bool operator<(const Zmod<Modulus> &other) const override;
  bool operator>(const Zmod<Modulus> &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;

  static Zmod<Modulus> one();
  static Zmod<Modulus> zero();
};

#endif
