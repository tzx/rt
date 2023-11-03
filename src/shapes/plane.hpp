#pragma once

#include "shape.hpp"

class Plane: public Shape {
  public:
    Plane() {};

    Tuple local_normal_at(const Tuple &local_p) const override;
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
};
