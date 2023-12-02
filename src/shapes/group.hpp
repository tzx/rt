#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Group: public Shape {
  public:
    Group() : bounds_(Bounds(Tuple::create_point(0, 0, 0), Tuple::create_point(0, 0, 0))) {};

    std::vector<Intersection> local_intersect(const Ray &local_r) override;
    Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const override;

    std::vector<std::shared_ptr<Shape>>& shapes();
    void add_child(std::shared_ptr<Shape> s);
    void set_material(std::shared_ptr<Material> m) override;

    Bounds bounds() const override;

  private:
    std::vector<std::shared_ptr<Shape>> shapes_;
    Bounds bounds_;

    // TODO: you can refactor check_axis
    std::pair<float, float> check_axis(float origin, float direction, float min_, float max_);
    bool intersect_bounding_box(const Ray &ray);

    std::shared_ptr<Material> material_;
};
