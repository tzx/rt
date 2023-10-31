#include <cmath>
#include <iostream>
#include <ostream>

#include "canvas/canvas.hpp"
#include "canvas/color.hpp"
#include "intersection.hpp"
#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"
#include "ray.hpp"
#include "sphere.hpp"


constexpr int CANVAS_DIMENSIONS = 500;
constexpr int wall_z = 10;
constexpr int wall_size = 7;
constexpr float pixel_size = (float)7/CANVAS_DIMENSIONS;
constexpr float half = 7/2.0f;

int main () {
  Tuple ray_origin = Tuple::create_point(0, 0, -5);
  Color color = Color(1, 0, 1);

  Canvas c = Canvas(CANVAS_DIMENSIONS, CANVAS_DIMENSIONS);
  Sphere shape = Sphere();
  shape.setTransform(Matrix::shearing(1, 0, 0, 0, 0, 0) * Matrix::scaling(0.5, 1, 1));

  for (auto y = 0; y < CANVAS_DIMENSIONS; ++y) {
    float world_y = half - pixel_size * y;
    for (auto x = 0; x < CANVAS_DIMENSIONS; ++x) {
      float world_x = -half + pixel_size * x;

      Tuple position = Tuple::create_point(world_x, world_y, wall_z);

      Ray r = Ray(ray_origin, (position - ray_origin).getNormalized());
      auto xs = intersect(shape, r);
      auto h = hit(xs);
      if (h.has_value()) {
        c.write_pixel(x, y, color);
      }
    }
  }
  std::cout << c.ppm();

  return 0;
}
