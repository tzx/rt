#pragma once

#include "pattern.hpp"
#include "../canvas/color.hpp"

class StripePattern: public Pattern {
  public:
    StripePattern(Color a, Color b);

    Color a() const;
    Color b() const;
    Color stripe_at(Tuple point) const;

  private:
    Color a_;
    Color b_;
};
