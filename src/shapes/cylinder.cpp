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

  if (t0 > t1) {
    std::swap(t0, t1);
  }

  std::vector<Intersection> xs;
  auto self = this->shared_from_this();

  auto y0 = local_r.origin().getY() + t0 * local_r.direction().getY();
  if (this->minimum() < y0 && y0 < this->maximum()) {
    xs.push_back(Intersection(t0, self));
  }

  auto y1 = local_r.origin().getY() + t1 * local_r.direction().getY();
  if (this->minimum() < y1 && y1 < this->maximum()) {
    xs.push_back(Intersection(t1, self));
  }

  return xs;
}

Tuple Cylinder::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(local_p.getX(), 0, local_p.getZ());
}

float Cylinder::minimum() const {
  return minimum_;
}

void Cylinder::set_minimum(float m) {
  minimum_ = m;
}

float Cylinder::maximum() const {
  return maximum_;
}

void Cylinder::set_maximum(float m) {
  maximum_ = m;
}
