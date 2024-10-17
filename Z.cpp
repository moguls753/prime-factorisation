#include "Z.h"

Z::Z(const mpz_class &value) : Ring(value) {}

Z Z::operator+(const Z &other) const { return Z(value + other.getValue()); }

Z Z::operator*(const Z &other) const { return Z(value * other.getValue()); }

Z Z::abs() const { return Z(::abs(value)); }

bool Z::operator!=(const Z &other) const { return (value != other.getValue()); }

bool Z::operator<(const Z &other) const { return (value < other.getValue()); }

bool Z::operator>(const Z &other) const { return (value > other.getValue()); }

void Z::print(std::ostream &os) const { os << value; }

bool Z::isUnit() const { return (value == -1 || value == 1); }
