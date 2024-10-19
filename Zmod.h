#ifndef ZMOD_H
#define ZMOD_H

#include "Ring.h"

template <int Modulus> class Zmod : public Ring<Zmod<Modulus>> {
private:
  mpz_class originalValue;

public:
  Zmod();
  Zmod(const mpz_class &value);
  mpz_class getOriginalValue() const;
  Zmod<Modulus> operator+(const Zmod<Modulus> &other) const override;
  Zmod<Modulus> operator-() const override;
  Zmod<Modulus> operator*(const Zmod<Modulus> &other) const override;
  Zmod<Modulus> abs() const override;
  bool operator!=(const Zmod<Modulus> &other) const override;
  bool operator<(const Zmod<Modulus> &other) const override;
  bool operator>(const Zmod<Modulus> &other) const override;
  void print(std::ostream &os) const override;
  bool isUnit() const override;
  Zmod<Modulus> invert() const override;
};

template <int Modulus> Zmod<Modulus>::Zmod() : Ring<Zmod<Modulus>>(0) {}

template <int Modulus>
Zmod<Modulus>::Zmod(const mpz_class &value)
    : Ring<Zmod<Modulus>>(value % Modulus) {
  originalValue = value;
}

template <int Modulus> mpz_class Zmod<Modulus>::getOriginalValue() const {
  return (this->originalValue);
}

template <int Modulus>
Zmod<Modulus> Zmod<Modulus>::operator+(const Zmod<Modulus> &other) const {
  return Zmod(this->value + other.value);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::operator-() const {
  return Zmod(-this->value);
}

template <int Modulus>
Zmod<Modulus> Zmod<Modulus>::operator*(const Zmod<Modulus> &other) const {
  return Zmod(this->value * other.value);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::abs() const {
  return Zmod(::abs(this->value));
}

template <int Modulus>
bool Zmod<Modulus>::operator!=(const Zmod<Modulus> &other) const {
  return (this->value != other.value);
}

template <int Modulus>
bool Zmod<Modulus>::operator<(const Zmod<Modulus> &other) const {
  return (this->value < other.value);
}

template <int Modulus>
bool Zmod<Modulus>::operator>(const Zmod<Modulus> &other) const {
  return (this->value > other.value);
}

template <int Modulus> void Zmod<Modulus>::print(std::ostream &os) const {
  os << this->value;
}

template <int Modulus> bool Zmod<Modulus>::isUnit() const {
  return (this->value != 0);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::invert() const {
  mpz_class result;
  mpz_class modulus = Modulus;
  if (mpz_invert(result.get_mpz_t(), this->value.get_mpz_t(),
                 modulus.get_mpz_t()) == 0) {
    throw std::invalid_argument("Kein Inverses vorhanden");
  }
  return Zmod(result);
}
#endif
