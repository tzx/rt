#pragma once

#include "../primitives/tuple.hpp"
#include "triangle.hpp"

class SmoothTriangle : public Triangle {
public:
  SmoothTriangle(Tuple p1, Tuple p2, Tuple p3, Tuple n1, Tuple n2, Tuple n3)
      : Triangle(p1, p2, p3) {
    this->n1_ = n1;
    this->n2_ = n2;
    this->n3_ = n3;
  };

  Tuple n1() const;
  Tuple n2() const;
  Tuple n3() const;

  std::vector<Intersection> local_intersect(const Ray &local_r) override;
  Tuple local_normal_at(const Tuple &point, const Intersection &hit) const override;

private:
  Tuple n1_;
  Tuple n2_;
  Tuple n3_;
};
