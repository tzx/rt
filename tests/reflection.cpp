#include <catch2/catch.hpp>
#include <cmath>
#include <memory>

#include "../src/lights/material.hpp"
#include "../src/shapes/plane.hpp"
#include "../src/canvas/world.hpp"
#include "../src/intersection.hpp"

TEST_CASE("Reflectivity for the default material", "[reflection]") {
  Material m = Material();
  REQUIRE( m.reflective() == 0.0 );
}

TEST_CASE("Precomputing the reflection vector", "[reflection]") {
  Plane shape = Plane();
  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2)/2.0f;
  Ray r = Ray(Tuple::create_point(0, 1, -1), Tuple::create_vector(0, -sq2_2, sq2_2));
  Intersection i = Intersection(sq2, std::make_shared<Plane>(shape));

  Computations comps = Computations(i, r);

  REQUIRE (comps.reflectv() == Tuple::create_vector(0, sq2_2, sq2_2));
}

TEST_CASE("The reflected color for a nonreflective material", "[reflection]") {
  World w = World::default_world();
  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));

  auto shape = w.objects().at(1);
  shape->material()->setAmbient(1);

  auto i = Intersection(1, shape);
  auto comps = Computations(i, r);

  Color color = w.reflected_color(comps);

  REQUIRE(color == Color(0, 0, 0));
}

TEST_CASE("The reflected color for a reflective material", "[reflection]") {
  World w = World::default_world();
  auto shape = Plane();
  shape.material()->setReflective(0.5);
  shape.setTransform(Matrix::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2)/2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3), Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.reflected_color(comps);

  REQUIRE(color == Color(0.190491, 0.238114, 0.142868));
}

TEST_CASE("shade_hit() with a reflective material", "[reflection]") {
  World w = World::default_world();
  auto shape = Plane();
  shape.material()->setReflective(0.5);
  shape.setTransform(Matrix::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2)/2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3), Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.shade_hit(comps);

  REQUIRE(color == Color(0.876886, 0.924509, 0.829263));
}

TEST_CASE ("color_at() with mutally reflective surfaces", "[reflection]") {
  World w = World();
  w.setLight(PointLight(Tuple::create_point(0, 0, 0), Color(1, 1, 1)));

  auto lower = std::make_shared<Plane>();
  lower->material()->setReflective(1);
  lower->setTransform(Matrix::translation(0, -1, 0));

  auto upper = std::make_shared<Plane>();
  upper->material()->setReflective(1);
  upper->setTransform(Matrix::translation(0, 1, 0));

  w.addObject(lower);
  w.addObject(upper);

  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 1, 0));

  Color c = w.color_at(r);

  // This reaches here and terminates
  REQUIRE ( true );
}

TEST_CASE("The reflected color at the maximum recursive depth", "[reflection]") {
  World w = World::default_world();
  auto shape = Plane();
  shape.material()->setReflective(0.5);
  shape.setTransform(Matrix::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2)/2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3), Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.reflected_color(comps, 0);

  REQUIRE(color == Color(0, 0, 0));
}
