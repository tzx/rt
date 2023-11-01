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

  Canvas c = Canvas(CANVAS_DIMENSIONS, CANVAS_DIMENSIONS);

  Material mat = Material();
  mat.setColor(Color(1, 0.2, 1));
  Sphere shape = Sphere();
  shape.setMaterial(mat);
  // shape.setTransform(Matrix::shearing(1, 0, 0, 0, 0, 0) * Matrix::scaling(0.5, 1, 1));

  Tuple light_position = Tuple::create_point(-10, 10, -10);
  Color light_color = Color(1, 1, 1);
  PointLight light = PointLight(light_position, light_color);

  for (auto y = 0; y < CANVAS_DIMENSIONS; ++y) {
    float world_y = half - pixel_size * y;
    for (auto x = 0; x < CANVAS_DIMENSIONS; ++x) {
      float world_x = -half + pixel_size * x;

      Tuple position = Tuple::create_point(world_x, world_y, wall_z);

      Ray r = Ray(ray_origin, (position - ray_origin).getNormalized());
      auto xs = intersect(shape, r);
      auto h = hit(xs);
      if (h.has_value()) {
        auto intersection = h.value();
        auto point = r.position(intersection.t());
        auto normal = intersection.object().normal_at(point);
        auto eye = -r.direction();
        auto color = intersection.object().material().lighting(light, point, eye, normal);

        c.write_pixel(x, y, color);
      }
    }
  }
  std::cout << c.ppm();

  return 0;
}
