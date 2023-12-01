#include "smooth_triangle.hpp"
#include <math.h>
#include "../util/approx.hpp"

Tuple SmoothTriangle::n1() const {
  return n1_;
}

Tuple SmoothTriangle::n2() const {
  return n2_;
}

Tuple SmoothTriangle::n3() const {
  return n3_;
}

Tuple SmoothTriangle::local_normal_at(const Tuple &point, const Intersection &hit)  const {
  return n2() * hit.u() +
         n3() * hit.v() +
         n1() * (1 - hit.u() - hit.v());
}

std::vector<Intersection> SmoothTriangle::local_intersect(const Ray &local_r) {
  auto dir_cross_e2 = crossProduct(local_r.direction(), this->e2());
  auto det = dotProduct(this->e1(), dir_cross_e2);
  if (fabs(det) < EPS) {
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
  return { Intersection(t, self, u, v) };
}
