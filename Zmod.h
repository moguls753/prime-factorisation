#ifndef ZMOD_H
#define ZMOD_H

#include "Ring.h"

class Zmod : public Ring<Zmod> {
private:
  int modulus;

public:
  Zmod() : Ring(0) {}
  Zmod(const mpz_class &value, int modulus);
  mpz_class reducedValue() const;
  Zmod operator+(const Zmod &other) const override;
  Zmod operator*(const Zmod &other) const override;
  Zmod abs() const override;
  bool operator!=(const Zmod &other) const override;
  bool operator<(const Zmod &other) const override;
  bool operator>(const Zmod &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;
};

#endif
