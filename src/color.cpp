#include "color.hpp"
#include "tuple.hpp"

Color::Color(float _r, float _g, float _b) : Tuple(_r, _g, _b, 0) {}

float Color::r() const {
  return getX();
}

float Color::g() const {
  return getY();
}

float Color::b() const {
  return getZ();
}
