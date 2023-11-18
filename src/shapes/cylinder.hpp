#pragma once

#include "shape.hpp"

class Cylinder: public Shape {
  public:
    Cylinder() {};
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;
};
