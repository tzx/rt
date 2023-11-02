#pragma once

#include "../lights/point_light.hpp"
#include "../sphere.hpp"
#include <memory>
#include <optional>
#include <vector>

class World {
  public:
    World();
    static World default_world();

    const std::optional<std::shared_ptr<PointLight>> light() const;
    const std::vector<std::shared_ptr<Sphere>> objects() const;

    bool contains(Sphere &sph) const;

  private:
    std::optional<std::shared_ptr<PointLight>> light_;
    std::vector<std::shared_ptr<Sphere>> objects_;
};
