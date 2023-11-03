#pragma once
#include "sphere.hpp"
#include <utility>
#include <optional>

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
std::optional<Intersection> hit(const std::vector<Intersection>&);

class Computations {
  public:
    Computations(const Intersection &i, const Ray &r);
    float t() const;
    Sphere object() const;
    Tuple point() const;
    Tuple eyev() const;
    Tuple normalv() const;
    bool inside() const;

    Tuple over_point() const;

  private:
    float t_;
    Sphere sph;
    Tuple point_;
    Tuple eyev_;
    Tuple normalv_;
    bool inside_;
};
