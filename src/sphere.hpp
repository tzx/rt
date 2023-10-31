#pragma once

#include "ray.hpp"
#include <vector>

class Sphere {
  public:
    // Assume center is 0, 0, 0 and that the radius of the sphere is 1
    Sphere();
    std::vector<float> intersect(Ray ray) const;

  private:
    int uuid;
};
