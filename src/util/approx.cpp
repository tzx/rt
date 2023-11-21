#include "approx.hpp"
#include <cmath>
#include <limits>

bool approx_eq(float a, float b) {
  if (a == std::numeric_limits<float>::infinity() || b == std::numeric_limits<float>::infinity() ||
      a == -std::numeric_limits<float>::infinity() || b == -std::numeric_limits<float>::infinity()) {
    return a == b;
  }
  return std::abs(a - b) < EPS;
}
