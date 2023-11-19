#include "cone.hpp"
#include "../util/approx.hpp"
#include "cylinder.hpp"
#include <cmath>
#include <iostream>

std::vector<Intersection> Cone::local_intersect(const Ray &r) {
  float a = r.direction().getX() * r.direction().getX() -
            r.direction().getY() * r.direction().getY() +
            r.direction().getZ() * r.direction().getZ();

  float b = 2 * r.origin().getX() * r.direction().getX() -
            2 * r.origin().getY() * r.direction().getY() +
            2 * r.origin().getZ() * r.direction().getZ();
  
  float c = r.origin().getX() * r.origin().getX() -
            r.origin().getY() * r.origin().getY() +
            r.origin().getZ() * r.origin().getZ();

  if (approx_eq(0, a) && approx_eq(0, b)) {
    std::vector<Intersection> xs;
    intersect_caps(r, xs);
    return xs;
  }

  auto self = this->shared_from_this();

  if (approx_eq(0, a) && !approx_eq(0, b)) {
    std::vector<Intersection> xs;
    float t = -c/(2.0 * b);
    auto y = r.origin().getY() + t * r.direction().getY();
    if (this->minimum() < y && y < this->maximum()) {
      xs.push_back(Intersection(t, self));
    }
    intersect_caps(r, xs);
    return xs;
  }

  float disc = b * b - 4 * a * c;
  if (fabs(disc) < EPS) {
    disc = 0;
  }

  if (disc < 0) {
    return {};
  }

  float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
  float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

  if (t0 > t1) {
    std::swap(t0, t1);
  }

  std::vector<Intersection> xs;

  auto y0 = r.origin().getY() + t0 * r.direction().getY();
  if (this->minimum() < y0 && y0 < this->maximum()) {
    xs.push_back(Intersection(t0, self));
  }

  auto y1 = r.origin().getY() + t1 * r.direction().getY();
  if (this->minimum() < y1 && y1 < this->maximum()) {
    xs.push_back(Intersection(t1, self));
  }

  // Check caps
  intersect_caps(r, xs);

  return xs;

}

float Cone::maximum() const {
  return maximum_;
}

void Cone::set_maximum(float m) {
  this->maximum_ = m;
}

float Cone::minimum() const {
  return minimum_;
}

void Cone::set_minimum(float m) {
  this->minimum_ = m;
}

bool Cone::closed() const {
  return closed_;
}

void Cone::set_closed(bool b) {
  this->closed_ = b;
}

void Cone::intersect_caps(const Ray &ray, std::vector<Intersection> &xs) {
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

Tuple Cone::local_normal_at(const Tuple &local_p) const {
  auto dist = local_p.getX() * local_p.getX() + local_p.getZ()* local_p.getZ();

  if (dist < 1 && local_p.getY() >= maximum() - EPS) {
    return Tuple::create_vector(0, 1, 0);
  }

  if (dist < 1 && local_p.getY() <= minimum() + EPS) {
    return Tuple::create_vector(0, -1, 0);
  }

  auto y = std::sqrt( local_p.getX() * local_p.getX() + local_p.getZ() * local_p.getZ() );
  if (local_p.getY() > 0) {
    y = -y;
  }

  return Tuple::create_vector(local_p.getX(), y, local_p.getZ());
}

bool Cone::check_cap(const Ray &ray, float t) const {
  auto x = ray.origin().getX() + t * ray.direction().getX();
  auto z = ray.origin().getZ() + t * ray.direction().getZ();

  auto radius = fabs( ray.origin().getY() + t * ray.direction().getY() );

  return (x * x + z * z) <= radius + EPS;
}
