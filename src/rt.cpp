#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "canvas/camera.hpp"
#include "canvas/canvas.hpp"
#include "canvas/color.hpp"
#include "canvas/world.hpp"
#include "intersection.hpp"
#include "lights/point_light.hpp"
#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"
#include "ray.hpp"
#include "shapes/sphere.hpp"


constexpr int CANVAS_DIMENSIONS = 500;
constexpr int wall_z = 10;
constexpr int wall_size = 7;
constexpr float pixel_size = (float)7/CANVAS_DIMENSIONS;
constexpr float half = 7/2.0f;

int main () {
  auto floor = std::make_shared<Sphere>();
  floor->setTransform(Matrix::scaling(10, 0.01, 10));
  auto m = floor->material();
  m->setColor(Color(1, 0.9, 0.9));
  m->setSpecular(0);

  auto left_wall = std::make_shared<Sphere>();
  left_wall->setTransform(Matrix::translation(0, 0, 5) * Matrix::rotation_y(-M_PI_4f) * Matrix::rotation_x(M_PI_2f) * Matrix::scaling(10, 0.01, 10));
  left_wall->set_material(floor->material());

  auto right_wall = std::make_shared<Sphere>();
  right_wall->setTransform(Matrix::translation(0, 0, 5) * Matrix::rotation_y(M_PI_4f) * Matrix::rotation_x(M_PI_2f) * Matrix::scaling(10, 0.01, 10));
  right_wall->set_material(floor->material());

  auto middle = std::make_shared<Sphere>();
  middle->setTransform(Matrix::translation(-0.5, 1, 0.5));
  auto middle_m = middle->material();
  middle_m->setColor(Color(0.1, 1, 0.5));
  middle_m->setDiffuse(0.7);
  middle_m->setSpecular(0.3);

  auto right = std::make_shared<Sphere>();
  right->setTransform(Matrix::translation(1.5, 0.5, -0.5) * Matrix::scaling(0.5, 0.5, 0.5));
  auto right_m = right->material();
  right_m->setColor(Color(0.5, 1, 0.1));
  right_m->setDiffuse(0.7);
  right_m->setSpecular(0.3);

  auto left = std::make_shared<Sphere>();
  left->setTransform(Matrix::translation(-1.5, 0.33, -0.75) * Matrix::scaling(0.33, 0.33, 0.33));
  auto left_m = left->material();
  left_m->setColor(Color(1, 0.8, 0.1));
  left_m->setDiffuse(0.7);
  left_m->setSpecular(0.3);

  World w = World();
  w.setLight(PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1)));
  w.addObject(floor);
  w.addObject(left_wall);
  w.addObject(right_wall);
  w.addObject(middle);
  w.addObject(right);
  w.addObject(left);

  Camera c = Camera(1000, 500, M_PIf/3.0f);
  c.setTransform(view_transform(Tuple::create_point(0, 1.5, -5), 
                                Tuple::create_point(0, 1, 0),
                                Tuple::create_vector(0, 1, 0)));
  
  Canvas canvas = c.render(w);

  std::cout << canvas.ppm();

  return 0;
}
