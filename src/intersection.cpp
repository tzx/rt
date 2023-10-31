#include "intersection.hpp"
#include <cmath>
#include <iostream>
#include <utility>

Intersection::Intersection(float t, Sphere s) {
  this->time = t;
  this->sph = s;
}

float Intersection::t() const {
  return this->time;
}

Sphere Intersection::object() const {
  return this->sph;
}

bool Intersection::operator==(const Intersection &oth) const {
  return this->t() == oth.t() && this->object() == oth.object();
}

std::vector<Intersection> intersect(const Sphere s, const Ray ray) {
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

  Intersection i1 = Intersection(t1, s);
  Intersection i2 = Intersection(t2, s);

  return {i1, i2};
}

std::pair<bool, const Intersection*> hit(const std::vector<Intersection> &xs) {
  const Intersection *result = nullptr;
  for (auto &i: xs) {
    if (i.t() < 0) {
      continue;
    }
    if (result == nullptr || i.t() < result->t()) {
      result = &i;
      std::cout << "switched" << std::endl;
    }
  }
  return {result != nullptr, result};
}
