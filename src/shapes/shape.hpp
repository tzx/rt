#pragma once

#include "../lights/material.hpp"
#include "../primitives/matrix.hpp"
#include "../ray.hpp"
#include "../intersection.hpp"
#include <memory>

// https://en.cppreference.com/w/cpp/language/abstract_class
class Shape {
  public:
    Shape();
    virtual ~Shape() = default;

    int uuid() const;
    Matrix transform() const;
    void setTransform(Matrix m);
    std::shared_ptr<Material> material();

    // TODO: This can't be const because of my test shape
    virtual std::vector<Intersection> local_intersect(const Ray &local_r) = 0;

  private:
    int uuid_;
    Matrix transform_;
    std::shared_ptr<Material> material_;
};

// TODO: can't be const
std::vector<Intersection> intersect (Shape &s, const Ray &ray);
