#include "sphere.hpp"
#include "primitives/matrix.hpp"
#include "util/randgen.hpp"


Sphere::Sphere() : transform_(Matrix::identity_matrix(4)) {
  // Assuming pretty decent distribution, we shouldn't be having collisions
  // At least for now....
  this->uuid_ = random_id();
}

int Sphere::uuid() const {
  return this->uuid_;
}

bool Sphere::operator==(const Sphere &other) const {
  return this->uuid() == other.uuid();
}

Matrix Sphere::transform() const {
  return this->transform_;
}

void Sphere::setTransform(Matrix m) {
  this->transform_ = m;
}
