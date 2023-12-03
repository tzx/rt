#include <catch2/catch.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../src/canvas/world.hpp"
#include "../src/intersections/intersection.hpp"
#include "../src/lights/material.hpp"
#include "../src/patterns/test_pattern.hpp"
#include "../src/shapes/plane.hpp"
#include "../src/shapes/sphere.hpp"
#include "../src/util/approx.hpp"

TEST_CASE("Reflectivity for the default material", "[reflection]") {
  Material m = Material();
  REQUIRE(m.reflective() == 0.0);
}

TEST_CASE("Precomputing the reflection vector", "[reflection]") {
  Plane shape = Plane();
  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2) / 2.0f;
  Ray r = Ray(Tuple::create_point(0, 1, -1),
              Tuple::create_vector(0, -sq2_2, sq2_2));
  Intersection i = Intersection(sq2, std::make_shared<Plane>(shape));

  Computations comps = Computations(i, r);

  REQUIRE(comps.reflectv() == Tuple::create_vector(0, sq2_2, sq2_2));
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
  shape.setTransform(Mat4::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2) / 2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3),
              Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.reflected_color(comps);

  REQUIRE(color == Color(0.190491, 0.238114, 0.142868));
}

TEST_CASE("shade_hit() with a reflective material", "[reflection]") {
  World w = World::default_world();
  auto shape = Plane();
  shape.material()->setReflective(0.5);
  shape.setTransform(Mat4::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2) / 2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3),
              Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.shade_hit(comps);

  REQUIRE(color == Color(0.876886, 0.924509, 0.829263));
}

TEST_CASE("color_at() with mutally reflective surfaces", "[reflection]") {
  World w = World();
  w.setLight(PointLight(Tuple::create_point(0, 0, 0), Color(1, 1, 1)));

  auto lower = std::make_shared<Plane>();
  lower->material()->setReflective(1);
  lower->setTransform(Mat4::translation(0, -1, 0));

  auto upper = std::make_shared<Plane>();
  upper->material()->setReflective(1);
  upper->setTransform(Mat4::translation(0, 1, 0));

  w.addObject(lower);
  w.addObject(upper);

  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 1, 0));

  Color c = w.color_at(r);

  // This reaches here and terminates
  REQUIRE(true);
}

TEST_CASE("The reflected color at the maximum recursive depth",
          "[reflection]") {
  World w = World::default_world();
  auto shape = Plane();
  shape.material()->setReflective(0.5);
  shape.setTransform(Mat4::translation(0, -1, 0));

  auto shapep = std::make_shared<Plane>(shape);
  w.addObject(shapep);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2) / 2.0f;

  Ray r = Ray(Tuple::create_point(0, 0, -3),
              Tuple::create_vector(0, -sq2_2, sq2_2));

  auto i = Intersection(sq2, shapep);
  auto comps = Computations(i, r);

  Color color = w.reflected_color(comps, 0);

  REQUIRE(color == Color(0, 0, 0));
}

TEST_CASE("Transparency and Refractive Index for the default material",
          "[refraction]") {
  Material m = Material();
  REQUIRE(m.transparency() == 0.0f);
  REQUIRE(m.refractive_index() == 1.0f);
}

TEST_CASE("A helper for producing a sphere with a glassy material",
          "[refraction]") {
  Sphere s = Sphere::glass_sphere();

  REQUIRE(s.transform() == Mat4::identity_matrix());
  REQUIRE(s.material()->transparency() == 1.0f);
  REQUIRE(s.material()->refractive_index() == 1.5f);
}

TEST_CASE("Finding n1 and n2 at various intersections", "[refraction]") {
  auto A = std::make_shared<Sphere>(Sphere::glass_sphere());
  A->setTransform(Mat4::scaling(2, 2, 2));
  A->material()->setRefractiveIndex(1.5);

  auto B = std::make_shared<Sphere>(Sphere::glass_sphere());
  B->setTransform(Mat4::translation(0, 0, -0.25));
  B->material()->setRefractiveIndex(2.0);

  auto C = std::make_shared<Sphere>(Sphere::glass_sphere());
  C->setTransform(Mat4::translation(0, 0, 0.25));
  C->material()->setRefractiveIndex(2.5);

  Ray r(Tuple::create_point(0, 0, -4), Tuple::create_vector(0, 0, 1));
  std::vector<Intersection> xs = {{2, A},    {2.75, B}, {3.25, C},
                                  {4.75, B}, {5.25, C}, {6, A}};

  auto comps = Computations(xs[0], r, xs);
  REQUIRE(comps.n1() == 1.0f);
  REQUIRE(comps.n2() == 1.5f);

  comps = Computations(xs[1], r, xs);
  REQUIRE(comps.n1() == 1.5f);
  REQUIRE(comps.n2() == 2.0f);

  comps = Computations(xs[2], r, xs);
  REQUIRE(comps.n1() == 2.0f);
  REQUIRE(comps.n2() == 2.5f);

  comps = Computations(xs[3], r, xs);
  REQUIRE(comps.n1() == 2.5f);
  REQUIRE(comps.n2() == 2.5f);

  comps = Computations(xs[4], r, xs);
  REQUIRE(comps.n1() == 2.5f);
  REQUIRE(comps.n2() == 1.5f);

  comps = Computations(xs[5], r, xs);
  REQUIRE(comps.n1() == 1.5f);
  REQUIRE(comps.n2() == 1.0f);
}

TEST_CASE("The under point is offset below the surface", "[refraction]") {
  Ray r(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  auto shape = std::make_shared<Sphere>(Sphere::glass_sphere());
  shape->setTransform(Mat4::translation(0, 0, 1));

  auto i = Intersection(5, shape);
  auto xs = intersect(shape, r);

  auto comps = Computations(i, r, xs);
  REQUIRE(comps.under_point().getZ() > SHADOW_OFFSET / 2.0f);
  REQUIRE(comps.point().getZ() < SHADOW_OFFSET / 2.0f);
}

TEST_CASE("The refracted color with an opaque surface", "[refraction]") {
  auto w = World::default_world();
  auto shape = w.objects().front();

  Ray r(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  std::vector<Intersection> xs = {{4, shape}, {6, shape}};

  auto comps = Computations(xs.at(0), r, xs);

  Color c = w.refracted_color(comps, 5);
  REQUIRE(c == Color(0, 0, 0));
}

TEST_CASE("The refracted color at the maximum recursion depth",
          "[refraction]") {
  auto w = World::default_world();
  auto shape = w.objects().front();
  shape->material()->setTransparency(1.0);
  shape->material()->setRefractiveIndex(1.5);

  Ray r(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  std::vector<Intersection> xs = {{4, shape}, {6, shape}};

  auto comps = Computations(xs.front(), r, xs);

  Color c = w.refracted_color(comps, 0);
  REQUIRE(c == Color(0, 0, 0));
}

TEST_CASE("The refracted color under total internal reflection",
          "[refraction]") {
  auto w = World::default_world();
  auto shape = w.objects().at(0);
  shape->material()->setTransparency(1.0);
  shape->material()->setRefractiveIndex(1.5);

  float sq2_2 = std::sqrt(2) / 2.0f;

  Ray r(Tuple::create_point(0, 0, sq2_2), Tuple::create_vector(0, 1, 0));
  std::vector<Intersection> xs = {{-sq2_2, shape}, {sq2_2, shape}};
  auto comps = Computations(xs.at(1), r, xs);

  Color c = w.refracted_color(comps, 5);
  REQUIRE(c == Color(0, 0, 0));
}

TEST_CASE("The refracted color with a refracted ray", "[refraction]") {
  auto w = World::default_world();
  auto A = w.objects().front();
  A->material()->setAmbient(1.0);
  auto pattern = std::make_shared<TestPattern>();
  A->material()->setPattern(pattern);

  auto B = w.objects().at(1);
  B->material()->setTransparency(1.0);
  B->material()->setRefractiveIndex(1.5);

  Ray r(Tuple::create_point(0, 0, 0.1), Tuple::create_vector(0, 1, 0));

  std::vector<Intersection> xs = {
      {-0.9899, A}, {-0.4899, B}, {0.4899, B}, {0.9899, A}};

  auto comps = Computations(xs.at(2), r, xs);

  auto c = w.refracted_color(comps, 5);
  REQUIRE(c == Color(0, 0.997872, 0.047472));
}

TEST_CASE("shade_hit() with a transparent material", "[refraction]") {
  auto w = World::default_world();

  auto floor = std::make_shared<Plane>();
  floor->setTransform(Mat4::translation(0, -1, 0));
  floor->material()->setTransparency(0.5);
  floor->material()->setRefractiveIndex(1.5);
  w.addObject(floor);

  auto ball = std::make_shared<Sphere>();
  ball->material()->setColor(Color(1, 0, 0));
  ball->material()->setAmbient(0.5);
  ball->setTransform(Mat4::translation(0, -3.5, -0.5));
  w.addObject(ball);

  float sq2 = std::sqrt(2);
  float sq2_2 = std::sqrt(2) / 2.0f;

  Ray r(Tuple::create_point(0, 0, -3), Tuple::create_vector(0, -sq2_2, sq2_2));
  std::vector<Intersection> xs = {{sq2, floor}};

  auto comps = Computations(xs.front(), r, xs);
  Color c = w.shade_hit(comps, 5);

  REQUIRE( c == Color(0.936395, 0.686395, 0.686395) );
}

TEST_CASE("The Schlick approximation under total internal reflection", "[fresnel]") {
  auto s = std::make_shared<Sphere>(Sphere::glass_sphere());
  float sq2_2 = std::sqrt(2)/2.0f;
  Ray r(Tuple::create_point(0, 0, sq2_2), Tuple::create_vector(0, 1, 0));

  std::vector<Intersection> xs = {
    {-sq2_2, s}, {sq2_2, s}
  };

  auto comps = Computations(xs.at(1), r, xs);

  auto reflectance = comps.schlick();

  REQUIRE (reflectance == 1.0f);
}

TEST_CASE ("The Schlick approximation with a perpendicular viewing angle", "[fresnel]") {
  auto s = std::make_shared<Sphere>(Sphere::glass_sphere());
  Ray r(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 1, 0));

  std::vector<Intersection> xs = {
    {-1, s}, {1, s}
  };

  auto comps = Computations(xs.at(1), r, xs);
  auto reflectance = comps.schlick();

  REQUIRE (reflectance == Approx(0.04));
}

TEST_CASE ("The Schlick approximation with small angle and n2 > n1", "[fresnel]") {
  auto s = std::make_shared<Sphere>(Sphere::glass_sphere());
  Ray r(Tuple::create_point(0, 0.99, -2), Tuple::create_vector(0, 0, 1));

  std::vector<Intersection> xs = {
    {1.8589, s}
  };

  auto comps = Computations(xs.front(), r, xs);
  auto reflectance = comps.schlick();

  REQUIRE (reflectance == Approx(0.48873));
}

TEST_CASE ("shade_hit() with a reflective, transparent material", "[fresnel]") {
  auto w = World::default_world();
  float sq2_2 = std::sqrt(2)/2.0f;
  Ray r(Tuple::create_point(0, 0, -3), Tuple::create_vector(0, -sq2_2, sq2_2));

  auto floor = std::make_shared<Plane>();
  floor->setTransform(Mat4::translation(0, -1, 0));
  floor->material()->setReflective(0.5);
  floor->material()->setTransparency(0.5);
  floor->material()->setRefractiveIndex(1.5);
  w.addObject(floor);

  auto ball = std::make_shared<Sphere>();
  ball->material()->setColor(Color(1, 0, 0));
  ball->material()->setAmbient(0.5);
  ball->setTransform(Mat4::translation(0, -3.5, -0.5));
  w.addObject(ball);

  std::vector<Intersection> xs = {{(float)std::sqrt(2), floor}};

  auto comps = Computations(xs.front(), r, xs);

  Color c = w.shade_hit(comps, 5);

  REQUIRE (c == Color(0.933891, 0.696412, 0.692405));
}
