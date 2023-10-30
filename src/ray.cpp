#include "ray.hpp"
#include "primitives/tuple.hpp"

Ray::Ray(Tuple origin_, Tuple direction_) {
  this->orig_ = origin_;
  this->dir_ = direction_;
}

Tuple Ray::origin() const {
  return this->orig_;
}

Tuple Ray::direction() const {
  return this->dir_;
}
