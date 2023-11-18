#pragma once

#include "shape.hpp"
#include <limits>

class Cylinder: public Shape {
  public:
    Cylinder() {
      this->minimum_ = std::numeric_limits<float>::lowest();
      this->maximum_ = std::numeric_limits<float>::max();
    };
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;

    float minimum() const;
    float maximum() const;

    void set_minimum(float m);
    void set_maximum(float m);

  private:
    float minimum_;
    float maximum_;
};
