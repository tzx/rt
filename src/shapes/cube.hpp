#pragma once

#include "shape.hpp"
#include <utility>

class Cube: public Shape {
  public:
    Cube() {};

    Bounds bounds() const override;
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const override;
  private:
    std::pair<float, float> check_axis(const float &origin, const float &direction);
};

