#include "stripe_pattern.hpp"
#include "../shapes/shape.hpp"
#include <cmath>

StripePattern::StripePattern(Color a, Color b) { 
  this->a_ = a;
  this->b_ = b;
}

Color StripePattern::a() const {
  return this->a_;
}

Color StripePattern::b() const {
  return this->b_;
}

Color StripePattern::stripe_at(Tuple point) const {
  int floored = std::floor(point.getX());
  if (floored % 2 == 0) {
    return a();
  }
  return b();
}
