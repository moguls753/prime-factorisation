#ifndef ZMOD_H
#define ZMOD_H

#include "ring.h"
#include <gmpxx.h>

class Zmod : public Ring<Zmod> {
private:
  mpz_class originalValue;
  mpz_class modulus;

public:
  Zmod() : Ring(0), modulus(0) {};
  Zmod(const mpz_class &value, const mpz_class &modulus);
  mpz_class getOriginalValue() const;
  mpz_class getModulus() const;
  Zmod operator+(const Zmod &other) const override;
  Zmod operator-() const override;
  Zmod operator*(const Zmod &other) const override;
  Zmod abs() const override;
  Zmod one() const override;
  Zmod zero() const override;
  bool operator!=(const Zmod &other) const override;
  bool operator==(const Zmod &other) const override;
  bool operator<(const Zmod &other) const override;
  bool operator>(const Zmod &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;
  bool isZero() const override;
  Zmod invert() const override;
};
#endif
