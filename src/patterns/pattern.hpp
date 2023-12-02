#pragma once

#include "../canvas/color.hpp"
#include "../primitives/matrix.hpp"

class Pattern {
  public:
    Pattern() : transform_(Matrix::identity_matrix(4)), transform_inverse_(Matrix::identity_matrix(4)) {}

    Matrix transform() const;
    Matrix transform_inverse() const;
    void set_transform(Matrix t);

    virtual Color pattern_at(Tuple point) const = 0;
    Color pattern_at_shape(const class Shape *obj, Tuple world_point) const;

  private:
    Matrix transform_;
    Matrix transform_inverse_;
};
