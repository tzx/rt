#include "test_shape.hpp"
#include <optional>

std::vector<Intersection> TestShape::local_intersect(const Ray &local_r) {
  this->saved_ray = std::optional<Ray>(local_r);
  return {};
}

Tuple TestShape::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(local_p.getX(), local_p.getY(), local_p.getZ());
}
