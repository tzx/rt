#include "sphere.hpp"
#include "primitives/matrix.hpp"
#include "util/randgen.hpp"


Sphere::Sphere() : transform_(Matrix::identity_matrix(4)) {
  // Assuming pretty decent distribution, we shouldn't be having collisions
  // At least for now....
  // We are also assuming that the sphere is always at the origin
  this->uuid_ = random_id();
  this->material_ = Material();
}

int Sphere::uuid() const {
  return this->uuid_;
}

bool Sphere::operator==(const Sphere &other) const {
  return this->uuid() == other.uuid() &&
         this->transform() == other.transform() &&
         this->material() == other.material();
}

Matrix Sphere::transform() const {
  return this->transform_;
}

void Sphere::setTransform(Matrix m) {
  this->transform_ = m;
}

Material Sphere::material() const {
  return this->material_;
}

void Sphere::setMaterial(Material m) {
  this->material_ = m;
}

Tuple Sphere::normal_at(Tuple world_p) const {
  // We assume that the point p is always on the surface of the sphere

  Tuple object_point = this->transform().inverse() * world_p;
  Tuple object_normal = object_point - Tuple::create_point(0, 0, 0);
  Tuple world_normal = this->transform().inverse().transpose() * object_normal;
  world_normal.turnIntoVector();

  return world_normal.getNormalized();
}
