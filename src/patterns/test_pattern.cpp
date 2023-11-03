#include "test_pattern.hpp"

Color TestPattern::pattern_at(Tuple point) const {
  return Color(point.getX(), point.getY(), point.getZ());
};
