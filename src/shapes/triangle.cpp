#include "triangle.hpp"
#include "bounds.hpp"
#include <algorithm>

Triangle::Triangle(Tuple p1, Tuple p2, Tuple p3) : bounds_(Tuple::create_point(0, 0, 0), Tuple::create_point(0, 0, 0)) {
  p1_ = p1;
  p2_ = p2;
  p3_ = p3;

  bounds_ = Bounds(Tuple::create_point(std::min({p1_.getX(), p2_.getX(), p3_.getX()}),
                                       std::min({p1_.getY(), p2_.getY(), p3_.getY()}),
                                       std::min({p1_.getZ(), p2_.getZ(), p3_.getZ()})),
                   Tuple::create_point(std::max({p1_.getX(), p2_.getX(), p3_.getX()}),
                                       std::max({p1_.getY(), p2_.getY(), p3_.getY()}),
                                       std::max({p1_.getZ(), p2_.getZ(), p3_.getZ()})));
}

Bounds Triangle::bounds() const {
  return bounds_;
}

std::vector<Intersection> Triangle::local_intersect(const Ray &local_r) {
  return {};
}

Tuple Triangle::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(0, 0, 0);
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
