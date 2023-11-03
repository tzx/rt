#include "ring.hpp"
#include <cmath>

Color Ring::a() const {
  return a_;
}

Color Ring::b() const {
  return b_;
}

Color Ring::pattern_at(Tuple point) const {
  int floored = std::floor(std::sqrt(point.getX() * point.getX() + point.getZ() * point.getZ()));
  if (floored % 2 == 0) {
    return a();
  }
  return b();
}
