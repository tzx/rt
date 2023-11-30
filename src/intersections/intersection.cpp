#include "intersection.hpp"
#include "../canvas/world.hpp"
#include "../shapes/shape.hpp"
#include <algorithm>
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

float Computations::n1() const {
  return this->n1_;
}

float Computations::n2() const {
  return this->n2_;
}

Computations::Computations(const Intersection &hit, const Ray &r, const std::vector<Intersection> &xs_) {
  this->t_ = hit.t();
  this->shape_ =hit.object();

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

  this->over_point_ = this->point() + this->normalv() * SHADOW_OFFSET;
  this->under_point_ = this->point() - this->normalv() * SHADOW_OFFSET;

  auto xs = xs_;
  if (xs.empty()) {
    xs = {hit};
  }

  std::vector<std::shared_ptr<Shape>> containers;
  for (auto &i: xs) {
    if (i == hit) {
      if (containers.empty()) {
        this->n1_ = 1.0;
      } else {
        this->n1_ = containers.back()->material()->refractive_index();
      }
    }

    auto occurence = std::find(containers.begin(), containers.end(), i.object());
    if (occurence != containers.end()) {
      containers.erase(occurence);
    } else {
      containers.push_back(i.object());
    }

    if (i == hit) {
      if (containers.empty()) {
        this->n2_ = 1.0;
      } else {
        this->n2_ = containers.back()->material()->refractive_index();
      }
      return;
    }
  }
}

Tuple Computations::over_point() const {
  return this->over_point_;
}

Tuple Computations::under_point() const {
  return this->under_point_;
}

float Computations::schlick() const {
  auto cos = dotProduct(eyev(), normalv());
  if (n1() > n2()) {
    auto n = n1() / n2();
    auto sin2_t = n * n * (1.0 - cos * cos);
    if (sin2_t > 1.0) {
      return 1.0;
    }

    auto cos_t = std::sqrt(1.0 - sin2_t);
    cos = cos_t;
  }
  auto r0 = (n1() - n2()) / (n1() + n2());
  r0 = r0 * r0;

  return r0 + (1 - r0) * std::pow(1 - cos, 5);
}
