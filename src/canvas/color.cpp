#include "color.hpp"
#include "../primitives/tuple.hpp"

Color::Color(float _r, float _g, float _b) : Tuple(_r, _g, _b, 0) {}

float Color::r() const {
  return getX();
}

float Color::g() const {
  return getY();
}

float Color::b() const {
  return getZ();
}

Color Color::operator+(const Color &oth) {
  return Color(this->r() + oth.r(), this->g() + oth.g(), this->b() + oth.b());
}

Color Color::operator-(const Color &oth) {
  return Color(this->r() - oth.r(), this->g() - oth.g(), this->b() - oth.b());
}

Color Color::operator*(const float &scal) {
  return Color(this->r() * scal, this->g() * scal, this->b() * scal);
}

Color Color::operator*(const Color &oth) {
  return Color(this->r() * oth.r(), this->g() * oth.g(), this->b() * oth.b());
}
