#pragma once

#include "../lights/point_light.hpp"
#include "../sphere.hpp"
#include "../intersection.hpp"
#include <memory>
#include <optional>
#include <vector>

class World {
  public:
    World();
    static World default_world();

    const std::optional<std::shared_ptr<PointLight>> light() const;
    void setLight(PointLight);
    const std::vector<std::shared_ptr<Sphere>> objects() const;

    bool contains(Sphere &sph) const;
    std::vector<Intersection> intersect_world(const Ray r) const;
    Color shade_hit(const Computations comps) const;

  private:
    std::optional<std::shared_ptr<PointLight>> light_;
    std::vector<std::shared_ptr<Sphere>> objects_;
};
