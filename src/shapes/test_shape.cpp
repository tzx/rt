#include "test_shape.hpp"
#include <optional>

std::vector<Intersection> TestShape::local_intersect(const Ray &local_r) {
  this->saved_ray = std::optional<Ray>(local_r);
  return {};
}
