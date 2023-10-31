#include "sphere.hpp"
#include "util/randgen.hpp"


Sphere::Sphere() {
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
