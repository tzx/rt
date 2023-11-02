#include "world.hpp"
#include <algorithm>
#include <memory>
#include <optional>
#include <vector>

World::World() {
  this->light_ = std::nullopt;
  this->objects_ = std::vector<std::shared_ptr<Sphere>>();
}

World World::default_world() {
  auto light = PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1));
  auto s1 = std::make_shared<Sphere>();
  auto m1 = Material();
  m1.setColor(Color(0.8, 1.0, 0.6));
  m1.setDiffuse(0.7);
  m1.setSpecular(0.2);
  s1->setMaterial(m1);

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

const std::vector<std::shared_ptr<Sphere>> World::objects() const {
  return this->objects_;
}

bool World::contains(Sphere &to_check) const {
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
    std::vector<Intersection> xs = intersect(*sph, r);
    res.insert(res.end(), xs.begin(), xs.end());
  }

  std::sort(res.begin(), res.end(), [](const Intersection &a, const Intersection &b) {
    return a.t() < b.t();
  });

  return res;
}

Color World::shade_hit(const Computations comps) const {
  return comps.object().material().lighting(*this->light().value(), comps.point(), comps.eyev(), comps.normalv());
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
