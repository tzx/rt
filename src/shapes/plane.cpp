#include "plane.hpp"
#include "../util/approx.hpp"
#include <cmath>

std::vector<Intersection> Plane::local_intersect(const Ray &local_r) {
  if (std::abs(local_r.direction().getY()) < EPS) {
    return {};
  }

  float t = -local_r.origin().getY() / local_r.direction().getY();

  return {Intersection(t, shared_from_this())};
}

Tuple Plane::local_normal_at(const Tuple &local_p, const Intersection &_) const {
  return Tuple::create_vector(0, 1, 0);
}

Bounds Plane::bounds() const {
  auto mi = std::numeric_limits<float>::lowest();
  auto ma = std::numeric_limits<float>::max();

  auto min_ = Tuple::create_point(mi, -0.1, mi);
  auto max_ = Tuple::create_point(ma, 0.1, ma);

  return Bounds(min_, max_);
}
