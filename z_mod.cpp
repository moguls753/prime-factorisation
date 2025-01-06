#include "z_mod.h"
#include <stdexcept>

Zmod::Zmod(const mpz_class &value, const mpz_class &modulus)
    : Ring<Zmod>(value % modulus), originalValue(value), modulus(modulus) {}

mpz_class Zmod::getOriginalValue() const { return (this->originalValue); }

mpz_class Zmod::getModulus() const { return (this->modulus); }

Zmod Zmod::operator+(const Zmod &other) const {
  if (modulus != other.modulus) {
    throw std::invalid_argument("Die Moduli müssen übereinstimmen");
  }
  return Zmod(this->value + other.value, modulus);
}

Zmod Zmod::operator-() const { return Zmod(modulus - this->value, modulus); }

Zmod Zmod::operator*(const Zmod &other) const {
  if (modulus != other.modulus) {
    throw std::invalid_argument("Die Moduli müssen übereinstimmen");
  }
  return Zmod(this->value * other.value, modulus);
}

Zmod Zmod::abs() const { return Zmod(::abs(this->value), modulus); }

Zmod Zmod::one() const { return Zmod(1, modulus); }

Zmod Zmod::zero() const { return Zmod(0, modulus); }

bool Zmod::operator!=(const Zmod &other) const {
  return (this->value != other.value) && (this->modulus == other.modulus);
}

bool Zmod::operator==(const Zmod &other) const {
  return (this->value == other.value) && (this->modulus == other.modulus);
}

bool Zmod::operator<(const Zmod &other) const {
  return (this->value < other.value) && (this->modulus == other.modulus);
}

bool Zmod::operator>(const Zmod &other) const {
  return (this->value > other.value) && (this->modulus == other.modulus);
}

void Zmod::print(std::ostream &os) const { os << this->value; }

bool Zmod::isUnit() const {
  mpz_class gcd;
  mpz_gcd(gcd.get_mpz_t(), this->value.get_mpz_t(), this->modulus.get_mpz_t());
  return (gcd == 1);
}

bool Zmod::isZero() const { return (value == 0); }

Zmod Zmod::invert() const {
  mpz_class result;
  if (mpz_invert(result.get_mpz_t(), this->value.get_mpz_t(),
                 modulus.get_mpz_t()) == 0) {
    throw std::invalid_argument("Kein Inverses vorhanden");
  }
  return Zmod(result, modulus);
}
