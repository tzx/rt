#include "point_light.hpp"

PointLight::PointLight(Tuple pos, Color inten) {
  this->pos_ = pos;
  this->intensity_ = inten;
}

Tuple PointLight::position() const {
  return this->pos_;
}

Color PointLight::intensity() const {
  return this->intensity_;
}
