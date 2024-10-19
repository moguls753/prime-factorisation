#ifndef RING_H
#define RING_H

#include <gmpxx.h>

template <typename T> class Ring {
protected:
  mpz_class value;

public:
  Ring(const mpz_class &value) : value(value) {};
  mpz_class getValue() const { return value; };
  virtual T operator+(const T &other) const = 0;
  virtual T operator-() const = 0;
  virtual T operator*(const T &other) const = 0;
  virtual T abs() const = 0;
  virtual bool operator!=(const T &other) const = 0;
  virtual bool operator<(const T &other) const = 0;
  virtual bool operator>(const T &other) const = 0;
  virtual void print(std::ostream &os) const = 0;
  friend std::ostream &operator<<(std::ostream &os, const Ring &ring) {
    ring.print(os);
    return os;
  }
  virtual bool isUnit() const = 0;
  virtual T invert() const = 0;
};

#endif
