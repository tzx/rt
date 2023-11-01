#pragma once

#include "lights/material.hpp"
#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"
#include "ray.hpp"

class Sphere {
  public:
    // Assume center is 0, 0, 0 and that the radius of the sphere is 1
    Sphere();

    int uuid() const;
    bool operator==(const Sphere &other) const;

    void setTransform(Matrix m);
    Matrix transform() const;
    Material material() const;
    void setMaterial(Material m);

    Tuple normal_at(Tuple p) const;

  private:
    int uuid_;
    Matrix transform_;
    Material material_;
};
