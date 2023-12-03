#pragma once

#include <cmath>
#include "../util/approx.hpp"

class Tuple {
  private:
    float x;
    float y;
    float z;
    float w;

  public:
    void repr() const;

    constexpr Tuple() : x(0), y(0), z(0), w(0) {}
    constexpr Tuple(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    constexpr static Tuple create_point(float x, float y, float z) { return Tuple(x, y, z, 1.0); }
    constexpr static Tuple create_vector(float x, float y, float z) { return Tuple(x, y, z, 0.0); }

    constexpr bool isPoint() const { return this->w == 1.0; }
    constexpr bool isVector() const { return this->w == 0.0; }
    constexpr float getX() const { return this->x; }
    constexpr float getY() const { return this->y; }
    constexpr float getZ() const { return this->z; }
    constexpr float getW() const { return this->w; }
    constexpr void turnIntoVector() { this->w = 0; }
    constexpr float getMagnitude() const { return std::sqrt(x * x + y * y + z * z + w * w); }
    constexpr const Tuple getNormalized() const { 
      auto mag = getMagnitude();
      return Tuple(x / mag, y / mag, z / mag, w / mag);
    }

    constexpr bool operator==(const Tuple &other) const {
      return approx_eq(x, other.x) &&
             approx_eq(y, other.y) &&
             approx_eq(z, other.z) &&
             approx_eq(w, other.w);
    }

    constexpr Tuple operator+(const Tuple &other) const {
      return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    constexpr Tuple operator-(const Tuple &other) const {
      return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    constexpr Tuple operator-() const {
      return Tuple(-x, -y, -z, -w);
    }

    constexpr Tuple operator*(const float &scalar) const {
      return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
    }

    constexpr Tuple operator/(const float &scalar) const {
      return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    }
};

constexpr float dotProduct(const Tuple &a, const Tuple &b) {
  return a.getX() * b.getX() +
         a.getY() * b.getY() +
         a.getZ() * b.getZ() +
         a.getW() * b.getW();
}

constexpr Tuple crossProduct(const Tuple &a, const Tuple &b) {
  return Tuple::create_vector(
      a.getY() * b.getZ() - a.getZ() * b.getY(),
      a.getZ() * b.getX() - a.getX() * b.getZ(),
      a.getX() * b.getY() - a.getY() * b.getX());
}

constexpr Tuple reflect(const Tuple &in, const Tuple &normal) {
  return in - normal * 2 * dotProduct(in, normal);
}
