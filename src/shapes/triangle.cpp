#include "triangle.hpp"
#include "bounds.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>

#include "../util/approx.hpp"

Triangle::Triangle(Tuple p1, Tuple p2, Tuple p3) : 
  bounds_(Tuple::create_point(std::min({p1.getX(), p2.getX(), p3.getX()}),
                              std::min({p1.getY(), p2.getY(), p3.getY()}),
                              std::min({p1.getZ(), p2.getZ(), p3.getZ()})),
          Tuple::create_point(std::max({p1.getX(), p2.getX(), p3.getX()}),
                              std::max({p1.getY(), p2.getY(), p3.getY()}),
                              std::max({p1.getZ(), p2.getZ(), p3.getZ()})))
{
  p1_ = p1;
  p2_ = p2;
  p3_ = p3;

}

Bounds Triangle::bounds() const {
  return bounds_;
}

std::vector<Intersection> Triangle::local_intersect(const Ray &local_r) {
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
  return { Intersection(t, self) };
}

Tuple Triangle::local_normal_at(const Tuple &local_p, const Intersection &_) const {
  return normal();
}

Tuple Triangle::p1() const {
  return p1_;
}

Tuple Triangle::p2() const {
  return p2_;
}

Tuple Triangle::p3() const {
  return p3_;
}

Tuple Triangle::e1() const {
  return p2() - p1();
}

Tuple Triangle::e2() const {
  return p3() - p1();
}

Tuple Triangle::normal() const {
  return crossProduct(e2(), e1()).getNormalized();
}
