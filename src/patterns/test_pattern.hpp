#pragma once

#include "pattern.hpp"

class TestPattern: public Pattern {
  public:
    TestPattern() {}

    Color pattern_at(Tuple point) const override;
};
