#include "ray.hpp"

Tuple Ray::position(float t) const {
  return this->origin() + this->direction() * t;
}

Ray Ray::transform(const Mat4 &m) const {
  auto new_orig = m * this->origin();
  auto new_dir = m * this->direction();
  return Ray(new_orig, new_dir);
}
