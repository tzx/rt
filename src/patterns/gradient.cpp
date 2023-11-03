#include "gradient.hpp"
#include <cmath>

Color Gradient::a() const {
  return this->a_;
}

Color Gradient::b() const {
  return this->b_;
}

Color Gradient::pattern_at(Tuple point) const {
  auto distance = b() - a();
  float fraction = point.getX() - std::floor(point.getX());
  return a() + distance * fraction;
}
