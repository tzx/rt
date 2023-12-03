#pragma once

#include "../primitives/matrix4.hpp"
#include "../primitives/tuple.hpp"

class Ray {
  public:
    Ray(Tuple origin_, Tuple direction_);
    const Tuple& origin() const;
    const Tuple& direction() const;

    Tuple position(float t) const;
    Ray transform(const Mat4 &m) const;

  private:
    Tuple orig_;
    Tuple dir_;
};
