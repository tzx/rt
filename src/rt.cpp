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
  Camera camera(1000, 500, M_PIf/3.0f);
  camera.setTransform(view_transform(Tuple::create_point(-2.6, 1.5, -3.9), 
                                     Tuple::create_point(-0.6, 1, -0.8),
                                     Tuple::create_point(0, 1, 0)));
  PointLight light(Tuple::create_point(-4.9, 4.9, -1), Color(1, 1, 1));

  auto wall_pattern = std::make_shared<StripePattern>(Color(0.45, 0.45, 0.45), Color(0.55, 0.55, 0.55));
  wall_pattern->set_transform(Matrix::rotation_y(M_PI_2f) * Matrix::scaling(0.25, 0.25, 0.25));
  auto wall_material = std::make_shared<Material>();
  wall_material->setPattern(wall_pattern);
  wall_material->setAmbient(0);
  wall_material->setDiffuse(0.4);
  wall_material->setSpecular(0);
  wall_material->setReflective(0.3);

  auto floor_pattern = std::make_shared<Checker>(Color(0.35, 0.35, 0.35), Color(0.65, 0.65, 0.65));
  auto floor_material = std::make_shared<Material>();
  floor_material->setPattern(floor_pattern);
  floor_material->setSpecular(0);
  floor_material->setReflective(0.4);
  auto floor = std::make_shared<Plane>();
  floor->set_material(floor_material);
  floor->setTransform(Matrix::rotation_y(M_PIf / 10.f));

  auto ceiling = std::make_shared<Plane>();
  auto ceiling_material = std::make_shared<Material>();
  ceiling_material->setColor(Color(0.8, 0.8, 0.8));
  ceiling_material->setAmbient(0.3);
  ceiling_material->setSpecular(0);
  ceiling->set_material(ceiling_material);
  ceiling->setTransform(Matrix::translation(0, 5, 0));

  auto west_wall = std::make_shared<Plane>();
  west_wall->set_material(wall_material);
  west_wall->setTransform(Matrix::translation(-5, 0, 0)
                        * Matrix::rotation_z(M_PI_2f)
                        * Matrix::rotation_y(M_PI_2f));
 
  auto east_wall = std::make_shared<Plane>();
  east_wall->set_material(wall_material);
  east_wall->setTransform(Matrix::translation(5, 0, 0)
                        * Matrix::rotation_z(M_PI_2f)
                        * Matrix::rotation_y(M_PI_2f));

  auto north_wall = std::make_shared<Plane>();
  north_wall->set_material(wall_material);
  north_wall->setTransform(Matrix::translation(0, 0, 5)
                        * Matrix::rotation_x(M_PI_2f));

  auto south_wall = std::make_shared<Plane>();
  south_wall->set_material(wall_material);
  south_wall->setTransform(Matrix::translation(0, 0, -5)
                        * Matrix::rotation_x(M_PI_2f));

  auto bsphere1 = std::make_shared<Sphere>();
  auto bsphere1_material = std::make_shared<Material>();
  bsphere1_material->setColor(Color(0.8, 0.5, 0.3));
  bsphere1_material->setShininess(50);
  bsphere1->set_material(bsphere1_material);
  bsphere1->setTransform(Matrix::translation(4.6, 0.4, 1) * Matrix::scaling(0.4, 0.4, 0.4));

  auto bsphere2 = std::make_shared<Sphere>();
  auto bsphere2_material = std::make_shared<Material>();
  bsphere2_material->setColor(Color(0.9, 0.4, 0.5));
  bsphere2_material->setShininess(50);
  bsphere2->set_material(bsphere2_material);
  bsphere2->setTransform(Matrix::translation(4.7, 0.3, 0.4) * Matrix::scaling(0.3, 0.3, 0.3));

  auto bsphere3 = std::make_shared<Sphere>();
  auto bsphere3_material = std::make_shared<Material>();
  bsphere3_material->setColor(Color(0.4, 0.9, 0.6));
  bsphere3_material->setShininess(50);
  bsphere3->set_material(bsphere3_material);
  bsphere3->setTransform(Matrix::translation(-1, 0.5, 4.5) * Matrix::scaling(0.5, 0.5, 0.5));

  auto bsphere4 = std::make_shared<Sphere>();
  auto bsphere4_material = std::make_shared<Material>();
  bsphere4_material->setColor(Color(0.4, 0.9, 0.9));
  bsphere4_material->setShininess(50);
  bsphere4->set_material(bsphere4_material);
  bsphere4->setTransform(Matrix::translation(-1.7, 0.3, 4.7) * Matrix::scaling(0.3, 0.3, 0.3));

  auto red_sphere = std::make_shared<Sphere>();
  auto red_sphere_material = std::make_shared<Material>();
  red_sphere_material->setColor(Color(1, 0.3, 0.2));
  red_sphere_material->setSpecular(0.4);
  red_sphere_material->setShininess(5);
  red_sphere->set_material(red_sphere_material);
  red_sphere->setTransform(Matrix::translation(-0.6, 1, 0.6));

  auto blue_sphere = std::make_shared<Sphere>();
  auto blue_sphere_material = std::make_shared<Material>();
  blue_sphere_material->setColor(Color(0, 0, 0.2));
  blue_sphere_material->setAmbient(0);
  blue_sphere_material->setDiffuse(0.4);
  blue_sphere_material->setSpecular(0.9);
  blue_sphere_material->setShininess(300);
  blue_sphere_material->setReflective(0.9);
  blue_sphere_material->setTransparency(0.9);
  blue_sphere_material->setRefractiveIndex(1.5);
  blue_sphere->set_material(blue_sphere_material);
  blue_sphere->setTransform(Matrix::translation(0.6, 0.7, -0.6)
                          * Matrix::scaling(0.7, 0.7, 0.7));

  auto green_sphere = std::make_shared<Sphere>();
  auto green_sphere_material = std::make_shared<Material>();
  green_sphere_material->setColor(Color(0, 0.2, 0));
  green_sphere_material->setAmbient(0);
  green_sphere_material->setDiffuse(0.4);
  green_sphere_material->setSpecular(0.9);
  green_sphere_material->setShininess(300);
  green_sphere_material->setReflective(0.9);
  green_sphere_material->setTransparency(0.9);
  green_sphere_material->setRefractiveIndex(1.5);
  green_sphere->set_material(green_sphere_material);
  green_sphere->setTransform(Matrix::translation(-0.7, 0.5, -0.8)
                          * Matrix::scaling(0.5, 0.5, 0.5));


  World w = World();
  w.setLight(light);
  w.addObject(floor);
  w.addObject(ceiling);
  w.addObject(west_wall);
  w.addObject(east_wall);
  w.addObject(north_wall);
  w.addObject(south_wall);
  w.addObject(bsphere1);
  w.addObject(bsphere2);
  w.addObject(bsphere3);
  w.addObject(bsphere4);
  w.addObject(red_sphere);
  w.addObject(blue_sphere);
  w.addObject(green_sphere);

  Canvas canvas = camera.render(w);

  std::cout << canvas.ppm();

  return 0;
}
