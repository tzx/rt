#pragma once

#include "shape.hpp"
#include <limits>

class Cylinder: public Shape {
  public:
    Cylinder() {
      this->minimum_ = std::numeric_limits<float>::lowest();
      this->maximum_ = std::numeric_limits<float>::max();
      this->closed_ = false;
    };
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;

    float minimum() const;
    float maximum() const;
    bool closed() const;

    Bounds bounds() const override;

    void set_minimum(float m);
    void set_maximum(float m);
    void set_closed(bool b);

  private:
    float minimum_;
    float maximum_;
    bool closed_;

    // checks intersection on the closed cylinder and adds them to xs
    void intersect_caps(const Ray &ray, std::vector<Intersection> &xs);
    // Checks to see if the intersection at 't' is within radius of 1 from the y axis
    bool check_cap(const Ray &ray, float t) const;
};
