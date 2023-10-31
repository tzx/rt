#pragma once

#include "primitives/matrix.hpp"
#include "ray.hpp"

class Sphere {
  public:
    // Assume center is 0, 0, 0 and that the radius of the sphere is 1
    Sphere();

    int uuid() const;
    bool operator==(const Sphere &other) const;

    void setTransform(Matrix m);
    Matrix transform() const;


  private:
    int uuid_;
    Matrix transform_;
};
