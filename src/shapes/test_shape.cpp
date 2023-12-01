#include "test_shape.hpp"
#include "bounds.hpp"
#include <limits>
#include <optional>

std::vector<Intersection> TestShape::local_intersect(const Ray &local_r) {
  this->saved_ray = std::optional<Ray>(local_r);
  return {};
}

Tuple TestShape::local_normal_at(const Tuple &local_p, const Intersection &_) const {
  return Tuple::create_vector(local_p.getX(), local_p.getY(), local_p.getZ());
}

Bounds TestShape::bounds() const {
  auto mi = std::numeric_limits<float>::lowest();
  auto ma = std::numeric_limits<float>::max();

  auto min_ = Tuple::create_point(mi, mi, mi);
  auto max_ = Tuple::create_point(ma, ma, ma);

  return Bounds(min_, max_);
}
