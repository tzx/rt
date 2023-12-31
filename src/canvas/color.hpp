#pragma once

#include "../primitives/tuple.hpp"

class Color: public Tuple {
  public:
    Color() = default;
    Color(float _r, float _g, float _b);

    float r() const;
    float g() const;
    float b() const;

    Color operator+(const Color &oth);
    Color operator-(const Color &oth);
    Color operator*(const float &scale);
    Color operator*(const Color &oth);
};
