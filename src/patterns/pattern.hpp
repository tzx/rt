#pragma once

#include "../primitives/matrix.hpp"

class Pattern {
  public:
    Pattern() : transform_(Matrix::identity_matrix(4)) {}

    Matrix transform() const;
    void set_transform(Matrix t);

  private:
    Matrix transform_;
};
