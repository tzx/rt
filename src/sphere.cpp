#include "sphere.hpp"
#include "primitives/tuple.hpp"
#include "util/randgen.hpp"
#include <cmath>
#include <vector>


Sphere::Sphere() {
  // Assuming pretty decent distribution, we shouldn't be having collisions
  // At least for now....
  this->uuid_ = random_id();
}

std::vector<float> Sphere::intersect(Ray ray) const {
  // Assume sphere is at world origin of 0,0,0
  Tuple sphere_to_ray = ray.origin() - Tuple::create_point(0, 0, 0);
  auto a = dotProduct(ray.direction(), ray.direction());
  auto b = 2 * dotProduct(ray.direction(), sphere_to_ray);
  auto c = dotProduct(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return {};
  }

  // Use quadratic formula
  // (-b +- sqrt(dis))/ 2a
  float t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
  float t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
  return {t1, t2};
}

int Sphere::uuid() const {
  return this->uuid_;
}

bool Sphere::operator==(const Sphere &other) const {
  return this->uuid() == other.uuid();
}
