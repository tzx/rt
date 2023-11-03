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

Tuple Plane::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(0, 1, 0);
}
