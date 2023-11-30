#pragma once

#include "../primitives/tuple.hpp"
#include "ray.hpp"
#include <memory>
#include <utility>
#include <optional>
#include <vector>

class Intersection {
  public:
    // Intersection();
    Intersection(float t, const std::shared_ptr<class Shape> &s);
    // XXX: It would be cool if i could separate the types of UV and non UV with dyn dispatch but idk how
    Intersection(float t, const std::shared_ptr<class Shape> &s, float u, float v);

    float t() const;
    float u() const;
    float v() const;
    const std::shared_ptr<class Shape> object() const;

    bool operator==(const Intersection &oth) const;

  private:
    float time;
    std::shared_ptr<Shape> shape_;
    float u_;
    float v_;
};

std::optional<Intersection> hit(const std::vector<Intersection>&);

class Computations {
  public:
    Computations(const Intersection &i, const Ray &r, const std::vector<Intersection> &xs = {});
    float t() const;
    std::shared_ptr<Shape> object() const;
    Tuple point() const;
    Tuple eyev() const;
    Tuple normalv() const;
    Tuple reflectv() const;
    bool inside() const;

    float n1() const;
    float n2() const;

    Tuple over_point() const;
    Tuple under_point() const;

    float schlick() const;

  private:
    float t_;
    std::shared_ptr<Shape> shape_;
    Tuple point_;
    Tuple eyev_;
    Tuple normalv_;
    Tuple reflectv_;
    bool inside_;

    float n1_;
    float n2_;

    Tuple over_point_;
    Tuple under_point_;
};
