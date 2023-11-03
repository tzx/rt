#include "shape.hpp"
#include "../util/randgen.hpp"
#include <memory>

Shape::Shape() : transform_(Matrix::identity_matrix(4)) {
  this->uuid_ = random_id();
  this->material_ = std::make_shared<Material>();
}

int Shape::uuid() const {
  return this->uuid_;
}

Matrix Shape::transform() const {
  return this->transform_;
}

void Shape::setTransform(Matrix m) {
  this->transform_ = m;
}

std::shared_ptr<Material> Shape::material() {
  return this->material_;
}

Tuple Shape::normal_at(const Tuple &p) const {
  Tuple local_point = this->transform().inverse() * p;
  Tuple local_normal = this->local_normal_at(local_point);
  Tuple world_normal = this->transform().inverse().transpose() * local_normal;
  world_normal.turnIntoVector();
  return world_normal.getNormalized();
}