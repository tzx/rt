#include "intersection.hpp"
#include "canvas/world.hpp"
#include "primitives/tuple.hpp"
#include "shapes/shape.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>

Intersection::Intersection(float t, const std::shared_ptr<Shape> &s) : time{t}, shape_{s} {};

float Intersection::t() const {
  return this->time;
}

const std::shared_ptr<Shape> Intersection::object() const {
  return this->shape_;
}

bool Intersection::operator==(const Intersection &oth) const {
  return this->t() == oth.t() && this->object() == oth.object();
}

std::vector<Intersection> intersect (std::shared_ptr<Shape> s, const Ray &ray) {
  Ray local_ray = ray.transform(s->transform().inverse());
  return s->local_intersect(local_ray);
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

std::shared_ptr<Shape> Computations::object() const {
  return this->shape_;
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

Tuple Computations::reflectv() const {
  return this->reflectv_;
}

bool Computations::inside() const {
  return this->inside_;
}

Computations::Computations(const Intersection &i, const Ray &r) {
  this->t_ = i.t();
  this->shape_ = i.object();

  this->point_ = r.position(this->t());
  this->eyev_ = -r.direction();
  this->normalv_ = this->object()->normal_at(this->point());


  this->reflectv_ = reflect(r.direction(), this->normalv_);

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
