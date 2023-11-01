#pragma once

#include "../primitives/tuple.hpp"
#include "../canvas/color.hpp"

class PointLight {
  public:
    PointLight(Tuple pos, Color inten);

    Tuple position() const;
    Color intensity() const;

  private:
    Tuple pos_;
    Color intensity_;
};
