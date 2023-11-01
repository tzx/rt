#include <cmath>
#include <iostream>
#include "../util/approx.hpp"
#include "tuple.hpp"

Tuple::Tuple(float a, float b, float c, float d) {
  x = a;
  y = b;
  z = c;
  w = d;
}

Tuple Tuple::create_point(float x, float y, float z) {
  return Tuple(x, y, z, 1.0);
}

Tuple Tuple::create_vector(float x, float y, float z) {
  return Tuple(x, y, z, 0.0);
}

float Tuple::getX() const {
  return x;
}

float Tuple::getY() const {
  return y;
}

float Tuple::getZ() const {
  return z;
}

float Tuple::getW() const {
  return w;
}

void Tuple::turnIntoVector() {
  this->w = 0;
}

bool Tuple::isPoint() const {
  return w == 1.0;
}

bool Tuple::isVector() const {
  return w == 0.0;
}

void Tuple::repr() const {
  std::cout << x << " " << y << " " << z << " " << w << std::endl;
}

float Tuple::getMagnitude() const {
  return std::sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::getNormalized() const {
  auto mag = getMagnitude();
  return Tuple(x / mag, y / mag, z / mag, w / mag);
}

bool Tuple::operator==(const Tuple &other) const {
  return approx_eq(this->getX(), other.getX()) &&
         approx_eq(this->getY(), other.getY()) &&
         approx_eq(this->getZ(), other.getZ()) &&
         approx_eq(this->getW(), other.getW());
}

Tuple Tuple::operator+(const Tuple &other) const {
  return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}

Tuple Tuple::operator-(const Tuple &other) const {
  return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}

Tuple Tuple::operator-() const {
  return Tuple(-x, -y, -z, -w);
}

Tuple Tuple::operator*(const float &scalar) const {
  return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
}

Tuple Tuple::operator/(const float &scalar) const {
  return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
}

float dotProduct(const Tuple &a, const Tuple &b) {
  return a.getX() * b.getX() +
         a.getY() * b.getY() +
         a.getZ() * b.getZ() +
         a.getW() * b.getW();
}

Tuple crossProduct(const Tuple &a, const Tuple &b) {
  // TODO: you should try to ensure that the Tuples are vectors?
  // Apparently this is very hard, so let's just use the homo coords
  return Tuple::create_vector(
      a.getY() * b.getZ() - a.getZ() * b.getY(),
      a.getZ() * b.getX() - a.getX() * b.getZ(),
      a.getX() * b.getY() - a.getY() * b.getX());
}

Tuple reflect(const Tuple in, const Tuple normal) {
  return in - normal * 2 * dotProduct(in, normal);
}
