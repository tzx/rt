#include "cube.hpp"
#include <array>
#include <limits>
#include <math.h>
#include <vector>

#include "../util/approx.hpp"

std::vector<Intersection> Cube::local_intersect(const Ray &ray) {
  auto [xtmin, xtmax] = check_axis(ray.origin().getX(), ray.direction().getX());
  auto [ytmin, ytmax] = check_axis(ray.origin().getY(), ray.direction().getY());
  auto [ztmin, ztmax] = check_axis(ray.origin().getZ(), ray.direction().getZ());

  auto tmin = std::max(std::max(xtmin, ytmin), ztmin);
  auto tmax = std::min(std::min(xtmax, ytmax), ztmax);

  if (tmin > tmax) {
    return {};
  }

  auto self = this->shared_from_this();
  return { Intersection(tmin, self), Intersection(tmax, self) };
}

Tuple Cube::local_normal_at(const Tuple &local_p) const {
  auto maxc = std::max(std::max(fabs(local_p.getX()), fabs(local_p.getY())), fabs(local_p.getZ()));

  if (approx_eq(maxc, fabs(local_p.getX()))) {
    return Tuple::create_vector(local_p.getX(), 0, 0);
  }

  if (approx_eq(maxc, fabs(local_p.getY()))) {
    return Tuple::create_vector(0, local_p.getY(), 0);
  }

  return Tuple::create_vector(0, 0, local_p.getZ());
}

Bounds Cube::bounds() const {
  return Bounds(Tuple::create_point(-1, -1, -1), Tuple::create_point(1, 1, 1));
}

std::pair<float, float> Cube::check_axis(const float &origin, const float &direction) {
  auto tmin_numerator = (-1 - origin);
  auto tmax_numerator = (1 - origin);

  float tmin;
  float tmax;
  if (fabs(direction) >= EPS) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * std::numeric_limits<float>::max();
    tmax = tmax_numerator * std::numeric_limits<float>::max();
  }
  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  return {tmin, tmax};
}
