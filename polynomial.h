#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "ring.h"
#include <cmath>
#include <concepts>
#include <iostream>
#include <ostream>
#include <vector>

template <typename R>
concept IsRing = std::derived_from<R, Ring<R>>;

template <IsRing R> class Polynomial {
private:
  std::vector<R> coefficients;
  std::vector<R> goingDownTheTree(const Polynomial<R> &f,
                                  const std::vector<Polynomial<R>> &tree,
                                  const int leftIndex, const int level,
                                  const int widthOffset);

public:
  Polynomial(const std::vector<R> &coefficients);
  int degree() const;
  std::vector<R> getCoefficients() const;
  R leadingCoefficient() const;
  Polynomial<R> operator+(const Polynomial<R> &other) const;
  Polynomial<R> operator-() const;
  Polynomial<R> operator*(const Polynomial<R> &other) const;
  std::pair<Polynomial<R>, Polynomial<R>>
  operator/(const Polynomial<R> &other) const;

  std::vector<R> evalAt(const std::vector<R> &points);

  void printAsSequence() const;
  void printAsFunction() const;
  void trim();
  std::vector<Polynomial<R>> buildSubproductTree(const std::vector<R> &points);
};

// Implementierung hier, da Template-Klasse
// Konstruktor
template <IsRing R>
Polynomial<R>::Polynomial(const std::vector<R> &coefficients)
    : coefficients(coefficients) {}

template <IsRing R> int Polynomial<R>::degree() const {
  for (int i = coefficients.size() - 1; i >= 0; i--) {
    if (!coefficients[i].isZero())
      return i;
  }
  // mathematisch gesehen hat das Nullpolynom den Grad -1, hier aber 0 aus
  // technischen Gründen: (coefficients[-1] ist nicht definiert in C++)
  // mit 0 spart man sich die Sonderfälle des Nullpolynoms
  return 0;
}

template <IsRing R> std::vector<R> Polynomial<R>::getCoefficients() const {
  return coefficients;
}

template <IsRing R> R Polynomial<R>::leadingCoefficient() const {
  if (coefficients.empty()) {
    throw std::runtime_error(
        "Cannot get leading coefficient of an empty polynomial");
  }
  return coefficients[degree()];
}

template <IsRing R> void Polynomial<R>::printAsSequence() const {
  if (coefficients.empty()) {
    std::cout << "()" << std::endl;
    return;
  }

  std::cout << "(";
  for (int i = 0; i < coefficients.size() - 1; i++) {
    std::cout << coefficients[i] << ", ";
  }
  std::cout << coefficients[coefficients.size() - 1];
  std::cout << ")" << std::endl;
}

template <IsRing R> void Polynomial<R>::printAsFunction() const {
  if (coefficients.empty()) {
    std::cout << "0" << std::endl;
    return;
  }
  for (int i = degree(); i >= 0; i--) {
    if (!coefficients[i].isZero()) {
      // Vorzeichen für höchsten Grad setzen?
      if (i == degree()) {
        if (coefficients[i] < coefficients[i].zero()) {
          std::cout << "-";
        }
      } else {
        std::cout << (coefficients[i] < coefficients[i].zero() ? " - " : " + ");
      }

      // Koeffizienten nur anzeigen, wenn sie nicht 1 oder -1 sind oder bei
      // Konstante (i == 0)
      if (coefficients[i].abs() != coefficients[i].one() || i == 0) {
        std::cout << coefficients[i].abs();
      }

      if (i > 0) {
        std::cout << "x";
        if (i > 1) {
          std::cout << "^" << i;
        }
      }
    }
  }
  std::cout << std::endl;
}

// Operationen auf Polynomen mit Koeffizienten aus dem Ring R
template <IsRing R>
Polynomial<R> Polynomial<R>::operator+(const Polynomial<R> &other) const {
  // dim(a+b) = max(dim(a), dim(b))
  int maxSize = std::max(coefficients.size(), other.coefficients.size());
  std::vector<R> resultCoefficients(maxSize);

  // "kürzeres" Polynom mit Nullen auffüllen, dann komponentenweise addieren
  for (int i = 0; i < maxSize; i++) {
    R coeff1 =
        (i < coefficients.size()) ? coefficients[i] : coefficients[i].zero();
    R coeff2 = (i < other.coefficients.size()) ? other.coefficients[i]
                                               : coefficients[i].zero();
    resultCoefficients[i] = coeff1 + coeff2;
  }
  return Polynomial(resultCoefficients);
}

template <IsRing R> Polynomial<R> Polynomial<R>::operator-() const {
  std::vector<R> negativeCoefficients(coefficients.size());

  for (int i = 0; i < negativeCoefficients.size(); i++) {
    negativeCoefficients[i] = -coefficients[i];
  }

  return Polynomial(negativeCoefficients);
}

template <IsRing R>
Polynomial<R> Polynomial<R>::operator*(const Polynomial<R> &other) const {
  if (coefficients.empty() || other.coefficients.empty()) {
    throw std::runtime_error(
        "Cannot multiply polynomials with no coefficients");
  }

  // dim(a*b) = dim(a) + dim(b) = resultCoefficients.size() - 1
  std::vector<R> resultCoefficients;
  resultCoefficients.reserve((degree() + other.degree()) + 1);

  // Faltung der Koeffizienten, also Distributivgesetz aka Ausmultiplizieren
  for (int k = 0; k <= (degree() + other.degree()); k++) {
    R sum = coefficients[0].zero();
    for (int i = 0; i <= k; i++) {
      // sicherstellen, dass hinter den Grenzen mit 0 multipliziert wird
      R c1 =
          (i < coefficients.size()) ? coefficients[i] : coefficients[0].zero();
      R c2 = ((k - i) < other.coefficients.size()) ? other.coefficients[k - i]
                                                   : coefficients[0].zero();
      sum = sum + c1 * c2;
    }
    resultCoefficients.push_back(sum);
  }
  return Polynomial<R>(resultCoefficients);
}

template <IsRing R>
std::pair<Polynomial<R>, Polynomial<R>>
Polynomial<R>::operator/(const Polynomial<R> &other) const {
  if (other.degree() > degree()) {
    throw std::invalid_argument("Der Grad des Divisors darf nicht grösser sein "
                                "als der des Dividenten!");
  }
  if (!other.leadingCoefficient().isUnit()) {
    throw std::invalid_argument(
        "Der Leitkoeffizient des Divisors ist keine Einheit in " +
        std::string(typeid(R).name()));
  }
  Polynomial<R> r = *this;
  R u = other.leadingCoefficient().invert();
  std::vector<R> q(degree() - other.degree() + 1,
                   other.leadingCoefficient().zero());
  for (int i = degree() - other.degree(); i >= 0; i--) {
    if (r.degree() == other.degree() + i) {
      q[i] = r.leadingCoefficient() * u;

      // Grad des Monoms muss passen
      std::vector<R> q_vector(r.degree() - other.degree(),
                              other.leadingCoefficient().zero());
      q_vector.push_back(q[i]);
      Polynomial<R> monom = Polynomial(q_vector);

      r = r + (-(monom * other));
    } else {
      q[i] = other.leadingCoefficient().zero();
    }
  }
  Polynomial<R> result = Polynomial(q);
  r.trim();
  return std::make_pair(result, r);
}

// Methoden für die "fast evaluation"(Algorithmus 10.7)
// TODO: Brauche ich die Wurzel überhaupt???
// NOTE: eigentlich hängt diese methode nicht von this ab, es könnte eine
// "freie" sein.
template <IsRing R>
std::vector<Polynomial<R>>
Polynomial<R>::buildSubproductTree(const std::vector<R> &points) {

  // zuerst werden die Blätter gesetzt
  std::vector<Polynomial<R>> tree;
  for (int i = 0; i < points.size(); i++) {
    tree.insert(tree.begin() + i, Polynomial<R>({-points[i], points[i].one()}));
  }

  // dann die Ebenen bis zur Wurzel, aber von rechts nach links. Also in
  // umgekehrter Reihenfolge zu 10.7!
  // die Tiefe des Baumes k ist durch log2(sizeof points) bestimmt.
  int k = std::log2(points.size());

  // offset für jede Ebene
  int levelOffset = 0;
  int width;
  for (int i = 1; i <= k; i++) {
    // std::cout << "Ebene " << i;
    // Breite auf dieser Ebene: 2^(k-i)
    // bit shifting für 2er Potenzen
    width = (1 << (k - i));
    for (int j = 0; j <= width - 1; j++) {
      // Die bereits berechneten Polynome aus dem Baum bestimmen:
      //  - begin() ist ein Iterator, begin() + 1 zeigt auf das
      //    zweite element und muss noch dereferenziert werden (*)
      //  - da das Array eindimensional ist, beginnt die zweite Ebene des Baumes
      //    an der Stelle tree.begin() + levelOffset

      Polynomial<R> M1 = *(tree.begin() + (2 * j) + levelOffset);
      Polynomial<R> M2 = *(tree.begin() + (2 * j + 1) + levelOffset);
      Polynomial<R> M = M1 * M2;
      tree.push_back(M);
    }
    levelOffset += 2 * width;
  }

  return tree;
}

template <IsRing R>
std::vector<R> Polynomial<R>::goingDownTheTree(
    const Polynomial<R> &f, const std::vector<Polynomial<R>> &tree,
    const int leftIndex, const int level, const int widthOffset) {

  if (f.degree() == 0)
    return f.getCoefficients();

  auto [q0, r0] = f / tree[leftIndex];
  auto [q1, r1] = f / tree[leftIndex + 1];

  // newIndex ist der Index des neuen linken Subproduktpolynoms
  int levelOffset = (1 << (level + 1));
  int newIndex = leftIndex - levelOffset + widthOffset;

  // Rekursion
  std::vector<R> leftResult =
      goingDownTheTree(r0, tree, newIndex, level + 1, 2 * widthOffset);
  std::vector<R> rightResult =
      goingDownTheTree(r1, tree, newIndex + 2, level + 1, 2 * widthOffset + 2);

  // merging, mit move Iterator effizienter da nciht kopiert wird.
  leftResult.insert(leftResult.end(),
                    std::make_move_iterator(rightResult.begin()),
                    std::make_move_iterator(rightResult.end()));
  return leftResult;
}

template <IsRing R>
std::vector<R> Polynomial<R>::evalAt(const std::vector<R> &points) {
  std::vector<Polynomial<R>> tree = this->buildSubproductTree(points);
  // for (int i = 0; i < tree.size(); i++) {
  //   tree[i].printAsSequence();
  // }
  std::vector<R> results =
      this->goingDownTheTree(*this, tree, tree.size() - 3, 1, 0);
  return results;
}

template <IsRing R> void Polynomial<R>::trim() {
  while (!coefficients.empty() && coefficients.back().isZero()) {
    coefficients.pop_back();
  }
}

#endif
