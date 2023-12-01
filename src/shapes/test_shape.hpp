#pragma once
#include "shape.hpp"
#include <optional>
#include <vector>

class TestShape : public Shape {
  public:
    TestShape() {};
    std::optional<Ray> saved_ray;
    std::vector<Intersection> local_intersect(const Ray &r) override;
    Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const override;

    Bounds bounds() const override;
};
