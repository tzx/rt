#include "approx.hpp"
#include <cmath>

bool approx_eq(float a, float b) {
  return std::abs(a - b) < EPS;
}
