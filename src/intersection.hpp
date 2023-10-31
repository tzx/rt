#pragma once
#include "sphere.hpp"
#include <utility>

class Intersection {
  public:
    Intersection();
    Intersection(float t, Sphere s);
    Intersection(Sphere s, Ray r);

    float t() const;
    Sphere object() const;

    bool operator==(const Intersection &oth) const;

  private:
    float time;
    Sphere sph;
};

std::vector<Intersection> intersect(const Sphere s, const Ray r);
std::pair<bool, const Intersection*> hit(const std::vector<Intersection>&);
