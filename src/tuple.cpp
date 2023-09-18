#include <iostream>
#include "tuple.hpp"

Tuple::Tuple(float a, float b, float c, float d) {
  x = a;
  y = b;
  z = c;
  w = d;
}

Tuple Tuple::create_point(float x, float y, float z) {
  return Tuple(x, y, z, 0.0);
}

Tuple Tuple::create_vector(float x, float y, float z) {
  return Tuple(x, y, z, 1.0);
}

float Tuple::getX() {
  return x;
}

float Tuple::getY() {
  return y;
}

float Tuple::getZ() {
  return z;
}

float Tuple::getW() {
  return w;
}

void Tuple::repr() {
  std::cout << x << " " << y << " " << z << " " << w << std::endl;
}
