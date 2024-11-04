#ifndef Z_H
#define Z_H

#include "Ring.h"

class Z : public Ring<Z> {
public:
  Z() : Ring(0) {}
  Z(const mpz_class &value);
  Z operator+(const Z &other) const override;
  Z operator*(const Z &other) const override;
  Z operator-() const override;
  Z abs() const override;
  bool operator!=(const Z &other) const override;
  bool operator==(const Z &other) const override;
  bool operator<(const Z &other) const override;
  bool operator>(const Z &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;
  Z invert() const override;
};

#endif
