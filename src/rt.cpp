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
#include "patterns/checker.hpp"
#include "patterns/gradient.hpp"
#include "patterns/ring.hpp"
#include "patterns/stripe_pattern.hpp"
#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"
#include "ray.hpp"
#include "shapes/plane.hpp"
#include "shapes/sphere.hpp"


constexpr int CANVAS_DIMENSIONS = 500;
constexpr int wall_z = 10;
constexpr int wall_size = 7;
constexpr float pixel_size = (float)7/CANVAS_DIMENSIONS;
constexpr float half = 7/2.0f;

int main () {
  auto checker = std::make_shared<Checker>(Color(1, 1, 1), Color(0, 0, 0));
  checker->set_transform(Matrix::rotation_y(M_PI_4f));

  auto floor = std::make_shared<Plane>();
  floor->material()->setPattern(checker);

  auto stripe = std::make_shared<StripePattern>(Color(0, 0, 1), Color(1, 0, 0));
  stripe->set_transform(Matrix::scaling(0.2, 0.2, 0.2) * Matrix::rotation_z(M_PI_4f));

  auto middle = std::make_shared<Sphere>();
  middle->setTransform(Matrix::translation(-0.5, 1, 0.5));
  auto middle_m = middle->material();
  middle_m->setColor(Color(0.1, 1, 0.5));
  middle_m->setDiffuse(0.7);
  middle_m->setSpecular(0.3);
  middle_m->setPattern(stripe);

  auto gradient = std::make_shared<Gradient>(Color(0, 1, 1), Color(0, 1, 0));
  gradient->set_transform(Matrix::scaling(0.9, 1, 1) * Matrix::rotation_y(M_PI_4f));

  auto right = std::make_shared<Sphere>();
  right->setTransform(Matrix::translation(1.5, 0.5, -0.5) * Matrix::scaling(0.5, 0.5, 0.5));
  auto right_m = right->material();
  right_m->setColor(Color(0.5, 1, 0.1));
  right_m->setDiffuse(0.7);
  right_m->setSpecular(0.3);
  right_m->setPattern(gradient);

  auto ring = std::make_shared<Ring>(Color(0, 1, 0), Color(0, 0.2, 0));
  ring->set_transform(Matrix::scaling(0.2, 0.2, 0.2) * Matrix::rotation_x(M_PI_2f) * Matrix::rotation_z(M_PI_4f));

  auto left = std::make_shared<Sphere>();
  left->setTransform(Matrix::translation(-1.5, 0.33, -0.45) * Matrix::scaling(0.33, 0.33, 0.33));
  auto left_m = left->material();
  left_m->setColor(Color(1, 0.8, 0.1));
  left_m->setDiffuse(0.7);
  left_m->setSpecular(0.3);
  left_m->setPattern(ring);

  World w = World();
  w.setLight(PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1)));
  w.addObject(floor);
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
