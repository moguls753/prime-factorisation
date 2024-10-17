#include "Zmod.h"
#include <gmpxx.h>

template <int Modulus> Zmod<Modulus>::Zmod() : Ring<Zmod<Modulus>>(0) {}

template <int Modulus>
Zmod<Modulus>::Zmod(const mpz_class &value) : Ring<Zmod<Modulus>>(value) {}

template <int Modulus> mpz_class Zmod<Modulus>::reducedValue() const {
  return (this->value % Modulus);
}

template <int Modulus>
Zmod<Modulus> Zmod<Modulus>::operator+(const Zmod<Modulus> &other) const {
  return Zmod(this->value + other.value, Modulus);
}

template <int Modulus>
Zmod<Modulus> Zmod<Modulus>::operator*(const Zmod<Modulus> &other) const {
  return Zmod<Modulus>(this->value * other.value, Modulus);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::abs() const {
  return Zmod(::abs(this->value), Modulus);
}

template <int Modulus>
bool Zmod<Modulus>::operator!=(const Zmod<Modulus> &other) const {
  return (reducedValue() != other.reducedValue());
}

template <int Modulus>
bool Zmod<Modulus>::operator<(const Zmod<Modulus> &other) const {
  return (this->value < other.getValue());
}

template <int Modulus>
bool Zmod<Modulus>::operator>(const Zmod<Modulus> &other) const {
  return (this->value > other.getValue());
}

template <int Modulus> void Zmod<Modulus>::print(std::ostream &os) const {
  os << this->value;
}

template <int Modulus> bool Zmod<Modulus>::isUnit() const {
  return (reducedValue() != 0);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::one() {
  return Zmod<Modulus>(1);
}

template <int Modulus> Zmod<Modulus> Zmod<Modulus>::zero() {
  return Zmod<Modulus>(0);
}
