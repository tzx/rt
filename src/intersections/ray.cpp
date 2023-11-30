#include "ray.hpp"

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

Tuple Ray::position(float t) const {
  return this->origin() + this->direction() * t;
}

Ray Ray::transform(Matrix m) const {
  auto new_orig = m * this->origin();
  auto new_dir = m * this->direction();
  return Ray(new_orig, new_dir);
}
