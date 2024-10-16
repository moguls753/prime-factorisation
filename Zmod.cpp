#include "Zmod.h"

Zmod::Zmod(const mpz_class &value, int modulus)
    : Ring(value), modulus(modulus) {}

mpz_class Zmod::reducedValue() const { return (value % modulus); }

Zmod Zmod::operator+(const Zmod &other) const {
  return Zmod(value + other.value, modulus);
}

Zmod Zmod::operator*(const Zmod &other) const {
  return Zmod(value * other.value, modulus);
}

Zmod Zmod::abs() const { return Zmod(::abs(value), modulus); }

bool Zmod::operator!=(const Zmod &other) const {
  return (reducedValue() != other.reducedValue());
}

bool Zmod::operator<(const Zmod &other) const {
  return (value < other.getValue());
}

bool Zmod::operator>(const Zmod &other) const {
  return (value > other.getValue());
}

void Zmod::print(std::ostream &os) const { os << value; }
