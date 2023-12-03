#include "triangle.hpp"
#include "bounds.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>

Bounds Triangle::bounds() const {
  return bounds_;
}

std::vector<Intersection> Triangle::local_intersect(const Ray &local_r) {
  auto dir_cross_e2 = crossProduct(local_r.direction(), this->e2());
  auto det = dotProduct(this->e1(), dir_cross_e2);
  if (std::abs(det) < EPS) {
    return {};
  }

  auto f = 1.0f / det;
  auto p1_to_origin = local_r.origin() - p1();
  auto u = f * dotProduct(p1_to_origin, dir_cross_e2);

  if (u < 0 || u > 1) {
    return {};
  }

  auto origin_cross_e1 = crossProduct(p1_to_origin, e1());
  auto v = f * dotProduct(local_r.direction(), origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return {};
  }

  auto t = f * dotProduct(e2(), origin_cross_e1);
  auto self = this->shared_from_this();
  return { Intersection(t, self) };
}

Tuple Triangle::local_normal_at(const Tuple &local_p, const Intersection &_) const {
  return normal();
}
