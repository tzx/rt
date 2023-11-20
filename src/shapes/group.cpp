#include "group.hpp"

std::vector<std::shared_ptr<Shape>>& Group::shapes() {
  return this->shapes_;
}

std::vector<Intersection> Group::local_intersect(const Ray &local_r) {
  return {};
}

Tuple Group::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(0, 0, 0);
}
