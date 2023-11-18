#include "cylinder.hpp"
#include "../util/approx.hpp"
#include <cmath>
#include <vector>

std::vector<Intersection> Cylinder::local_intersect(const Ray &local_r) {
  float a = local_r.direction().getX()  * local_r.direction().getX() +
           local_r.direction().getZ()  * local_r.direction().getZ();
  
  // It is parallel to the y axis
  if (approx_eq(0, a)) {
    return {};
  }

  float b = 2 * local_r.origin().getX() * local_r.direction().getX() +
           2 * local_r.origin().getZ() * local_r.direction().getZ();

  float c = local_r.origin().getX()  * local_r.origin().getX() + 
           local_r.origin().getZ()  * local_r.origin().getZ() -
           1;

  float disc = b * b - 4 * a * c;

  if (disc < 0) {
    return {};
  }

  float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
  float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

  auto self = this->shared_from_this();
  return { Intersection(t0, self), Intersection(t1, self) };
}

Tuple Cylinder::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(local_p.getX(), 0, local_p.getZ());
}
