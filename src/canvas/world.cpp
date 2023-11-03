#include "world.hpp"
#include <algorithm>
#include <memory>
#include <optional>
#include <vector>

#include "../shapes/sphere.hpp"

World::World() {
  this->light_ = std::nullopt;
  this->objects_ = std::vector<std::shared_ptr<Shape>>();
}

World World::default_world() {
  auto light = PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1));
  auto s1 = std::make_shared<Sphere>();
  s1->material()->setColor(Color(0.8, 1.0, 0.6));
  s1->material()->setDiffuse(0.7);
  s1->material()->setSpecular(0.2);

  auto s2 = std::make_shared<Sphere>();
  auto m2 = Matrix::scaling(0.5, 0.5, 0.5);
  s2->setTransform(m2);

  World w = World();
  w.light_ = std::optional<std::shared_ptr<PointLight>>(std::make_shared<PointLight>(light));
  w.objects_.push_back(s1);
  w.objects_.push_back(s2);

  return w;
}

const std::optional<std::shared_ptr<PointLight>> World::light() const {
  return this->light_;
}

void World::setLight(PointLight light) {
  this->light_ = std::make_shared<PointLight>(light);
}

const std::vector<std::shared_ptr<Shape>> World::objects() const {
  return this->objects_;
}

void World::addObject(std::shared_ptr<Shape> to_add) {
  this->objects_.push_back(to_add);
}

bool World::contains(Shape &to_check) const {
  for (auto sph: this->objects()) {
    if (to_check == *sph) {
      return true;
    }
  }
  return false;
}

std::vector<Intersection> World::intersect_world(const Ray r) const {
  std::vector<Intersection> res;
  for (auto sph: this->objects()) {
    std::vector<Intersection> xs = intersect(sph, r);
    res.insert(res.end(), xs.begin(), xs.end());
  }

  std::sort(res.begin(), res.end(), [](const Intersection &a, const Intersection &b) {
    return a.t() < b.t();
  });

  return res;
}

Color World::shade_hit(const Computations comps) const {
  bool in_shadow = this->is_shadowed(comps.over_point());
  return comps.object()->material()->lighting(comps.object().get(),
                                              *this->light().value(),
                                              comps.point(),
                                              comps.eyev(),
                                              comps.normalv(),
                                              in_shadow);
}

Color World::color_at(const Ray r) const {
  auto xs = this->intersect_world(r);
  std::optional<Intersection> h = hit(xs);
  if (h == std::nullopt) {
    return Color(0, 0, 0);
  }

  auto comps = Computations(h.value(), r);

  return this->shade_hit(comps);
}

bool World::is_shadowed(Tuple point) const {
  Tuple v = this->light().value()->position() - point;
  float distance = v.getMagnitude();
  Tuple direction = v.getNormalized();

  Ray r = Ray(point, direction);
  auto xs = this->intersect_world(r);
  auto h = hit(xs);

  return h.has_value() && h.value().t() < distance;
}
