#pragma once

#include "../lights/material.hpp"
#include "../primitives/matrix.hpp"
#include "../intersections/intersection.hpp"
#include "../intersections/ray.hpp"
#include "bounds.hpp"
#include <memory>

static auto fake_hit = Intersection();

// https://en.cppreference.com/w/cpp/language/abstract_class
// TODO: Right now intersections own a reference to shape but we create it in local_intersect so :sob:
class Shape : public std::enable_shared_from_this<Shape> {
  public:
    Shape();

    int uuid() const;
    Matrix transform() const;
    Matrix transform_inverse() const;
    void setTransform(Matrix m);
    std::shared_ptr<Material> material();
    virtual void set_material(std::shared_ptr<Material> m);
    std::shared_ptr<const Material> const_material() const;

    std::optional<std::shared_ptr<class Group>> parent() const;
    void set_parent(std::shared_ptr<class Group>);

    Tuple world_to_object(const Tuple &p) const;
    Tuple normal_at(const Tuple &p, const Intersection &hit) const;
    Tuple normal_to_world(const Tuple &normal) const;

    virtual Bounds bounds() const = 0;

    bool operator==(const Shape &other) const;

    // TODO: This can't be const because of my test shape
    virtual std::vector<Intersection> local_intersect(const Ray &local_r) = 0;
    virtual Tuple local_normal_at(const Tuple &local_p, const Intersection &hit) const = 0;

  private:
    int uuid_;
    Matrix transform_;
    Matrix transform_inverse_;
    std::shared_ptr<Material> material_;
    std::optional<std::shared_ptr<class Group>> parent_;
};

// TODO: can't be const
std::vector<Intersection> intersect(std::shared_ptr<Shape> s, const Ray &ray);
