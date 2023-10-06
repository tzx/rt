#include <iostream>
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

bool Tuple::isPoint() const {
  return w == 1.0;
}

bool Tuple::isVector() const {
  return w == 0.0;
}

void Tuple::repr() const {
  std::cout << x << " " << y << " " << z << " " << w << std::endl;
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
