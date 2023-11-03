#pragma once

#include "pattern.hpp"
class Ring: public Pattern {
  public:
    Ring(Color a, Color b) : a_(a), b_(b) {}
    Color a() const;
    Color b() const;

    Color pattern_at(Tuple point) const override;

  private:
    Color a_;
    Color b_;
};
