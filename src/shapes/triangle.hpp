#pragma once

#include "shape.hpp"
class Triangle: public Shape {
  public:
    Triangle(Tuple p1, Tuple p2, Tuple p3);

    Tuple p1() const;
    Tuple p2() const;
    Tuple p3() const;

    Tuple e1() const;
    Tuple e2() const;
    Tuple normal() const;

    Bounds bounds() const override;
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const override;

  private:
    Tuple p1_;
    Tuple p2_;
    Tuple p3_;

    Bounds bounds_;
};
