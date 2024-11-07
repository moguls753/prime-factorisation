#ifndef Z_H
#define Z_H

#include "ring.h"
#include <gmpxx.h>

class Z : public Ring<Z> {
public:
  Z() : Ring(0) {}
  Z(const mpz_class &value);
  Z operator+(const Z &other) const override;
  Z operator*(const Z &other) const override;
  Z operator-() const override;
  Z abs() const override;
  Z one() const override;
  Z zero() const override;
  bool operator!=(const Z &other) const override;
  bool operator==(const Z &other) const override;
  bool operator<(const Z &other) const override;
  bool operator>(const Z &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;
  bool isZero() const override;
  Z invert() const override;
};

#endif
