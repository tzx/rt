#pragma once

#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"

class Ray {
  public:
    Ray(Tuple origin_, Tuple direction_);
    Tuple origin() const;
    Tuple direction() const;

    Tuple position(float t) const;
    Ray transform(Matrix m) const;

  private:
    Tuple orig_;
    Tuple dir_;
};
