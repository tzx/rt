#include "group.hpp"
#include "shape.hpp"
#include <algorithm>
#include <memory>

std::vector<std::shared_ptr<Shape>>& Group::shapes() {
  return this->shapes_;
}

void Group::add_child(std::shared_ptr<Shape> s) {
  this->shapes_.push_back(s);

  auto base = this->shared_from_this();
  auto self = std::dynamic_pointer_cast<Group>(base);
  s->set_parent(self);
}

std::vector<Intersection> Group::local_intersect(const Ray &local_r) {
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

Tuple Group::local_normal_at(const Tuple &local_p) const {
  return Tuple::create_vector(0, 0, 0);
}
