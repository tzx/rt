#include "intersection.hpp"
#include "canvas/world.hpp"
#include "primitives/tuple.hpp"
#include "shapes/shape.hpp"
#include <cmath>
#include <iostream>
#include <optional>
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

std::vector<Intersection> intersect (Shape &s, const Ray &ray) {
  Ray local_ray = ray.transform(s.transform().inverse());
  return s.local_intersect(local_ray);
}

std::vector<Intersection> intersect(const Sphere s, const Ray ray_) {
  Ray ray = ray_.transform(s.transform().inverse());

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

std::optional<Intersection> hit(const std::vector<Intersection> &xs) {
  std::optional<Intersection> result = std::nullopt;
  for (auto i: xs) {
    if (i.t() < 0) {
      continue;
    }
    if (result == std::nullopt || i.t() < result.value().t()) {
      result = std::optional<Intersection>(i);
    }
  }
  return result;
}

float Computations::t() const {
  return this->t_;
}

Sphere Computations::object() const {
  return this->sph;
}

Tuple Computations::point() const {
  return this->point_;
}

Tuple Computations::eyev() const {
  return this->eyev_;
}

Tuple Computations::normalv() const {
  return this->normalv_;
}

bool Computations::inside() const {
  return this->inside_;
}

Computations::Computations(const Intersection &i, const Ray &r) {
  this->t_ = i.t();
  this->sph = i.object();

  this->point_ = r.position(this->t());
  this->eyev_ = -r.direction();
  this->normalv_ = this->object().normal_at(this->point());

  if (dotProduct(this->normalv(), this->eyev()) < 0) {
    this->inside_ = true;
    this->normalv_ = - this->normalv_;
  } else {
    this->inside_ = false;
  }
}

Tuple Computations::over_point() const {
    return this->point() + this->normalv() * SHADOW_OFFSET;
}
