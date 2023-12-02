#include "pattern.hpp"
#include "../shapes/shape.hpp"

void Pattern::set_transform(Matrix t) {
  this->transform_ = t;
  this->transform_inverse_ = t.inverse();
}

Matrix Pattern::transform() const {
  return this->transform_;
}

Matrix Pattern::transform_inverse() const {
  return this->transform_inverse_;
}

Color Pattern::pattern_at_shape(const Shape *obj, Tuple world_point) const {
  Tuple object_point = obj->transform_inverse() * world_point;
  Tuple pattern_point = this->transform_inverse() * object_point;

  return this->pattern_at(pattern_point);
}
