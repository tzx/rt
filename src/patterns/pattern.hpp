#pragma once

#include "../canvas/color.hpp"
#include "../primitives/matrix.hpp"

class Pattern {
  public:
    Pattern() : transform_(Matrix::identity_matrix(4)) {}

    Matrix transform() const;
    void set_transform(Matrix t);

    virtual Color stripe_at(Tuple point) const = 0;
    Color stripe_at_object(const class Shape *obj, Tuple world_point) const;

  private:
    Matrix transform_;
};
