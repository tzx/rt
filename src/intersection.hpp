#pragma once
#include "sphere.hpp"

class Intersection {
  public:
    Intersection(float t, Sphere s);
    Intersection(Sphere s, Ray r);

    float t() const;
    Sphere object() const;

  private:
    float time;
    Sphere sph;
};

std::vector<Intersection> intersect(const Sphere s, const Ray r);
