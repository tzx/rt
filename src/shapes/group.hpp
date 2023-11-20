#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Group: public Shape {
  public:
    Group() : bounds_(Bounds(Tuple::create_point(0, 0, 0), Tuple::create_point(0, 0, 0))) {};

    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;

    std::vector<std::shared_ptr<Shape>>& shapes();
    void add_child(std::shared_ptr<Shape> s);

    Bounds bounds() const override;

  private:
    std::vector<std::shared_ptr<Shape>> shapes_;
    Bounds bounds_;
};
