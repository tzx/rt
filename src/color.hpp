#pragma once

#include "tuple.hpp"

class Color: public Tuple {
  public:
    Color(float _r, float _g, float _b);

    float r() const;
    float g() const;
    float b() const;
};
