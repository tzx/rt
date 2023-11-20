#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Group: public Shape {
  public:
    Group() {};

    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;

    std::vector<std::shared_ptr<Shape>>& shapes();

  private:
    std::vector<std::shared_ptr<Shape>> shapes_;
};
