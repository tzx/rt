#pragma once

#include "shape.hpp"
#include <algorithm>
class Triangle: public Shape {
  public:
    Triangle(Tuple p1, Tuple p2, Tuple p3) :
      bounds_(Tuple::create_point(std::min({p1.getX(), p2.getX(), p3.getX()}),
                                  std::min({p1.getY(), p2.getY(), p3.getY()}),
                                  std::min({p1.getZ(), p2.getZ(), p3.getZ()})),
              Tuple::create_point(std::max({p1.getX(), p2.getX(), p3.getX()}),
                                  std::max({p1.getY(), p2.getY(), p3.getY()}),
                                  std::max({p1.getZ(), p2.getZ(), p3.getZ()}))),
      p1_(p1),
      p2_(p2),
      p3_(p3) {}

    constexpr const Tuple& p1() const { return p1_; }
    constexpr const Tuple& p2() const { return p2_; }
    constexpr const Tuple& p3() const { return p3_; }

    constexpr const Tuple e1() const { return p2() - p1(); }
    constexpr const Tuple e2() const { return p3() - p1(); }
    constexpr const Tuple normal() const { return crossProduct(e2(), e1()).getNormalized(); }

    Bounds bounds() const override;
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const override;

  private:
    Tuple p1_;
    Tuple p2_;
    Tuple p3_;

    Bounds bounds_;
};
