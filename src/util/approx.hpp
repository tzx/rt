#pragma once
#include <cmath>
#include <limits>

constexpr float EPS = 0.00001;
constexpr bool approx_eq(float a, float b) {
  if (a == std::numeric_limits<float>::infinity() || b == std::numeric_limits<float>::infinity() ||
      a == -std::numeric_limits<float>::infinity() || b == -std::numeric_limits<float>::infinity()) {
    return a == b;
  }
  return std::abs(a - b) < EPS;
}
