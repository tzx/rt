#pragma once

#include "sphere.hpp"

class Intersection {
  public:
    Intersection(float t, Sphere s);

    float t() const;
    Sphere object() const;

  private:
    float time;
    Sphere sph;
};
