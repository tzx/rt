#include "intersection.hpp"

Intersection::Intersection(float t, Sphere s) {
  this->time = t;
  this->sph = s;
}

float Intersection::t() const {
  return this->time;
}

Sphere Intersection::object() const {
  return this->sph;
}
