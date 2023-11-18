#include "cylinder.hpp"
#include "../util/approx.hpp"
#include "../intersection.hpp"
#include <cmath>
#include <iostream>
#include <vector>

std::vector<Intersection> Cylinder::local_intersect(const Ray &local_r) {
  float a = local_r.direction().getX()  * local_r.direction().getX() +
           local_r.direction().getZ()  * local_r.direction().getZ();
  
  // It is parallel to the y axis
  if (approx_eq(0, a)) {
    std::vector<Intersection> xs;
    intersect_caps(local_r, xs);
    return xs;
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

  // Check caps
  intersect_caps(local_r, xs);

  return xs;
}

Tuple Cylinder::local_normal_at(const Tuple &local_p) const {
  auto dist = local_p.getX() * local_p.getX() + local_p.getZ()* local_p.getZ();

  if (dist < 1 && local_p.getY() >= maximum() - EPS) {
    return Tuple::create_vector(0, 1, 0);
  }

  if (dist < 1 && local_p.getY() <= minimum() + EPS) {
    return Tuple::create_vector(0, -1, 0);
  }

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

bool Cylinder::closed() const {
  return closed_;
}

void Cylinder::set_closed(bool b) {
  closed_ = b;
}

void Cylinder::intersect_caps(const Ray &ray, std::vector<Intersection> &xs) {
  if (!closed() || approx_eq(0, ray.direction().getY())) {
    return;
  }

  auto self = this->shared_from_this();
  float t = (this->minimum() - ray.origin().getY()) / ray.direction().getY();
  if (check_cap(ray, t)) {
    xs.push_back(Intersection(t, self));
  }

  t = (this->maximum() - ray.origin().getY()) / ray.direction().getY();
  if (check_cap(ray, t)) {
    xs.push_back(Intersection(t, self));
  }
}

bool check_cap(const Ray &ray, float t) {
  auto x = ray.origin().getX() + t * ray.direction().getX();
  auto z = ray.origin().getZ() + t * ray.direction().getZ();

  return (x * x + z * z) <= 1 + EPS;
}
