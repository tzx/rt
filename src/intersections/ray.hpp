#pragma once

#include "../primitives/matrix4.hpp"
#include "../primitives/tuple.hpp"

class Ray {
  public:
    constexpr Ray(Tuple origin_, Tuple direction_) :
      orig_(origin_),
      dir_(direction_) {}

    constexpr const Tuple& origin() const { return this->orig_; }
    constexpr const Tuple& direction() const { return this->dir_; }

    Tuple position(float t) const;
    Ray transform(const Mat4 &m) const;

  private:
    Tuple orig_;
    Tuple dir_;
};
