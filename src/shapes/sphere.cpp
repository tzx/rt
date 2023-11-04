#include "sphere.hpp"
#include "../primitives/matrix.hpp"
#include "../util/randgen.hpp"
#include "../intersection.hpp"
#include "shape.hpp"
#include <cmath>
#include <memory>

Tuple Sphere::local_normal_at(const Tuple &local_p) const {
  return local_p - Tuple::create_point(0, 0, 0);
}

Sphere Sphere::glass_sphere() {
  Sphere s;
  s.material()->setTransparency(1.0);
  s.material()->setRefractiveIndex(1.5);

  return s;
}

std::vector<Intersection> Sphere::local_intersect(const Ray &local_r) {
  // Assume sphere is at world origin of 0,0,0
  Tuple sphere_to_local_r = local_r.origin() - Tuple::create_point(0, 0, 0);
  auto a = dotProduct(local_r.direction(), local_r.direction());
  auto b = 2 * dotProduct(local_r.direction(), sphere_to_local_r);
  auto c = dotProduct(sphere_to_local_r, sphere_to_local_r) - 1;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return {};
  }

  // Use quadratic formula
  // (-b +- sqrt(dis))/ 2a
  float t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
  float t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

  Intersection i1 = Intersection(t1, this->shared_from_this());
  Intersection i2 = Intersection(t2, this->shared_from_this());

  return {i1, i2};
}
