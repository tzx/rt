#include "world.hpp"
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

const std::vector<std::shared_ptr<Sphere>> World::objects() const {
  return this->objects_;
}

bool World::contains(Sphere &to_check) const {
  for (auto sph: this->objects_) {
    if (to_check == *sph) {
      return true;
    }
  }
  return false;
}
