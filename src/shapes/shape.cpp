#include "shape.hpp"
#include "../util/randgen.hpp"
#include <memory>
#include <optional>
#include "group.hpp"

Shape::Shape() : transform_(Matrix::identity_matrix(4)), transform_inverse_(Matrix::identity_matrix(4)) {
  this->uuid_ = random_id();
  this->material_ = std::make_shared<Material>();
}

bool Shape::operator==(const Shape &other) const {
  return this->uuid() == other.uuid() &&
         this->transform() == other.transform() &&
         *(this->const_material()) == *other.const_material();
}

int Shape::uuid() const {
  return this->uuid_;
}

Matrix Shape::transform() const {
  return this->transform_;
}

Matrix Shape::transform_inverse() const {
  return this->transform_inverse_;
}

void Shape::setTransform(Matrix m) {
  this->transform_ = m;
  this->transform_inverse_ = m.inverse();
}

std::shared_ptr<Material> Shape::material() {
  return this->material_;
}

void Shape::set_material(std::shared_ptr<Material> m) {
  this->material_ = m;
}

std::shared_ptr<const Material> Shape::const_material() const {
  return this->material_;
}

Tuple Shape::normal_at(const Tuple &p, const Intersection &hit) const {
  auto local_point = world_to_object(p);
  auto local_normal = local_normal_at(local_point, hit);
  return normal_to_world(local_normal);
}

Tuple Shape::normal_to_world(const Tuple &normal_) const {
  Tuple normal = this->transform_inverse().transpose() * normal_;
  normal.turnIntoVector();
  normal = normal.getNormalized();

  if (this->parent().has_value()) {
    auto par = this->parent().value();
    normal = par->normal_to_world(normal);
  }
  return normal;
}

Tuple Shape::world_to_object(const Tuple &p_) const {
  Tuple p = p_;
  if (this->parent().has_value()) {
    std::shared_ptr<Group> par = this->parent().value();
    p = par->world_to_object(p);
  }
  return this->transform_inverse() * p;
}

std::optional<std::shared_ptr<Group>> Shape::parent() const {
  return this->parent_;
}

void Shape::set_parent(std::shared_ptr<Group> group) {
  this->parent_ = std::make_optional(group);
}
