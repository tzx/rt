#pragma once

#include "pattern.hpp"
#include "../canvas/color.hpp"
#include "../primitives/matrix.hpp"

class StripePattern: public Pattern {
  public:
    StripePattern(Color a, Color b);

    Color a() const;
    Color b() const;
    Color stripe_at(Tuple point) const override;

  private:
    Color a_;
    Color b_;
};
