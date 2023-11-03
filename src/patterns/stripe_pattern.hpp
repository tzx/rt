#pragma once

#include "pattern.hpp"
#include "../canvas/color.hpp"
#include "../primitives/matrix.hpp"

class StripePattern: public Pattern {
  public:
    StripePattern(Color a, Color b);

    Color a() const;
    Color b() const;
    Color stripe_at(Tuple point) const;
    Color stripe_at_object(const class Shape *obj, Tuple world_point) const;

  private:
    Color a_;
    Color b_;
};
