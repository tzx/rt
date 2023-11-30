#pragma once

#include "../lights/material.hpp"
#include "../primitives/matrix.hpp"
#include "../primitives/tuple.hpp"
#include "../intersections/ray.hpp"
#include "../intersections/intersection.hpp"
#include "shape.hpp"

class Sphere : public Shape {
  public:
    // Assume center is 0, 0, 0 and that the radius of the sphere is 1
    Sphere() {};

    static Sphere glass_sphere();

    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;
    Bounds bounds() const override;
};
