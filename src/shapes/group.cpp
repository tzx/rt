#include "group.hpp"
#include "shape.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <memory>

#include "../util/approx.hpp"

std::vector<std::shared_ptr<Shape>>& Group::shapes() {
  return this->shapes_;
}

void Group::set_material(std::shared_ptr<Material> m) {
  this->Shape::set_material(m);
  for (auto &s: this->shapes_) {
    s->set_material(m);
  }
}

void Group::add_child(std::shared_ptr<Shape> s) {
  s->set_material(this->material());
  this->shapes_.push_back(s);

  auto base = this->shared_from_this();
  auto self = std::dynamic_pointer_cast<Group>(base);
  s->set_parent(self);

  auto parent_bounds = s->bounds().transform(s->transform());
  this->bounds_.merge(parent_bounds);
}

std::vector<Intersection> Group::local_intersect(const Ray &local_r) {
  if (!intersect_bounding_box(local_r)) {
    return {};
  }

  std::vector<Intersection> res;
  for (auto& s: shapes_) {
    auto xs = intersect(s, local_r);
    res.insert(res.end(), xs.begin(), xs.end());
  }

  std::sort(res.begin(), res.end(), [](const Intersection &a, const Intersection &b) {
    return a.t() < b.t();
  });

  return res;
}

Tuple Group::local_normal_at(const Tuple &local_p, const Intersection &_) const {
  return Tuple::create_vector(0, 0, 0);
}

Bounds Group::bounds() const {
  return bounds_;
}

std::pair<float, float> Group::check_axis(float origin, float direction, float min_, float max_) {
  auto tmin_numerator = (min_ - origin);
  auto tmax_numerator = (max_ - origin);

  float tmin;
  float tmax;
  if (fabs(direction) >= EPS) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * std::numeric_limits<float>::infinity();
    tmax = tmax_numerator * std::numeric_limits<float>::infinity();
  }
  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  return {tmin, tmax};
}

bool Group::intersect_bounding_box(const Ray &ray) {
  auto [xtmin, xtmax] = check_axis(ray.origin().getX(), ray.direction().getX(),
                                   bounds().minimum().getX(), bounds().maximum().getX());
  auto [ytmin, ytmax] = check_axis(ray.origin().getY(), ray.direction().getY(),
                                   bounds().minimum().getY(), bounds().maximum().getY());
  auto [ztmin, ztmax] = check_axis(ray.origin().getZ(), ray.direction().getZ(),
                                   bounds().minimum().getZ(), bounds().maximum().getZ());

  auto tmin = std::max({xtmin, ytmin, ztmin});
  auto tmax = std::min({xtmax, ytmax, ztmax});

  return tmin < tmax;
}
