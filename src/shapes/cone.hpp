#pragma once

#include "shape.hpp"
#include <limits>

class Cone: public Shape {
  public:
    Cone() {
      this->minimum_ = std::numeric_limits<float>::lowest();
      this->maximum_ = std::numeric_limits<float>::max();
      this->closed_ = false;
    };
    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p) const override;

    float minimum() const;
    float maximum() const;
    bool closed() const;

    void set_minimum(float m);
    void set_maximum(float m);
    void set_closed(bool b);

  private:
    float minimum_;
    float maximum_;
    bool closed_;

    void intersect_caps(const Ray &ray, std::vector<Intersection> &xs);
    // Radius changes 
    bool check_cap(const Ray &ray, float t) const;
};