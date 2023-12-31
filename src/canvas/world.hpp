#pragma once

#include "../lights/point_light.hpp"
#include "../shapes/shape.hpp"
#include "../intersections/intersection.hpp"
#include <memory>
#include <optional>
#include <vector>

constexpr float SHADOW_OFFSET = 0.001f;

class World {
  public:
    World();
    static World default_world();

    const std::optional<std::shared_ptr<PointLight>> light() const;
    void setLight(PointLight);
    const std::vector<std::shared_ptr<Shape>> objects() const;
    void addObject(std::shared_ptr<Shape> to_add);

    bool contains(Shape &sph) const;
    std::vector<Intersection> intersect_world(const Ray &r) const;
    Color shade_hit(const Computations &comps, size_t remaining = 4) const;
    Color color_at(const Ray r, size_t remaining = 4) const;
    Color reflected_color(const Computations &comps, size_t remaining = 4) const;
    Color refracted_color(const Computations &comps, size_t remaining) const;
    bool is_shadowed(Tuple point) const;

  private:
    std::optional<std::shared_ptr<PointLight>> light_;
    std::vector<std::shared_ptr<Shape>> objects_;
};
