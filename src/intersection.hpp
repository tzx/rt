#pragma once

#include "primitives/tuple.hpp"
#include "ray.hpp"
#include <memory>
#include <utility>
#include <optional>
#include <vector>

class Intersection {
  public:
    Intersection();
    Intersection(float t, const std::shared_ptr<class Shape> &s);

    float t() const;
    const std::shared_ptr<class Shape> object() const;

    bool operator==(const Intersection &oth) const;

  private:
    float time;
    std::shared_ptr<Shape> shape_;
};

std::optional<Intersection> hit(const std::vector<Intersection>&);

class Computations {
  public:
    Computations(const Intersection &i, const Ray &r);
    float t() const;
    std::shared_ptr<Shape> object() const;
    Tuple point() const;
    Tuple eyev() const;
    Tuple normalv() const;
    bool inside() const;

    Tuple over_point() const;

  private:
    float t_;
    std::shared_ptr<Shape> shape_;
    Tuple point_;
    Tuple eyev_;
    Tuple normalv_;
    bool inside_;
};
