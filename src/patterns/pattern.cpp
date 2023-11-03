#include "pattern.hpp"
#include "../shapes/shape.hpp"

void Pattern::set_transform(Matrix t) {
  this->transform_ = t;
}

Matrix Pattern::transform() const {
  return this->transform_;
}

Color Pattern::stripe_at_object(const Shape *obj, Tuple world_point) const {
  Tuple object_point = obj->transform().inverse() * world_point;
  Tuple pattern_point = this->transform().inverse() * object_point;

  return this->stripe_at(pattern_point);
}
