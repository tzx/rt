#include "checker.hpp"
#include <cmath>

Color Checker::a() const {
  return a_;
}

Color Checker::b() const {
  return b_;
}

Color Checker::pattern_at(Tuple point) const {
  int floored_sum = std::floor(point.getX()) + std::floor(point.getY()) + std::floor(point.getZ());
  if (floored_sum % 2 == 0) {
    return a();
  }
  return b();
}
