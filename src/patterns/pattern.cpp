#include "pattern.hpp"

void Pattern::set_transform(Matrix t) {
  this->transform_ = t;
}

Matrix Pattern::transform() const {
  return this->transform_;
}
