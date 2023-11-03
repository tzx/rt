#include <catch2/catch.hpp>

#include "../src/canvas/color.hpp"
#include "../src/patterns/gradient.hpp"
#include "../src/patterns/stripe_pattern.hpp"
#include "../src/patterns/test_pattern.hpp"
#include "../src/lights/material.hpp"
#include "../src/shapes/sphere.hpp"

TEST_CASE("Creating a stripe pattern", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.a() == white);
  REQUIRE(pattern.b() == black);
}

TEST_CASE("A stripe pattern is constant in y", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 1, 0)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 2, 0)) == white);
}

TEST_CASE("A stripe pattern is constant in z", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 1)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 2)) == white);
}

TEST_CASE("A stripe pattern alternates in x", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(0.9, 0, 0)) == white);
  REQUIRE(pattern.pattern_at(Tuple::create_point(1, 0, 0)) == black);
  REQUIRE(pattern.pattern_at(Tuple::create_point(-0.1, 0, 0)) == black);
  REQUIRE(pattern.pattern_at(Tuple::create_point(-1, 0, 0)) == black);
  REQUIRE(pattern.pattern_at(Tuple::create_point(-1.1, 0, 0)) == white);
}

TEST_CASE("Lighting with a pattern applied", "[material]") {
  Material m = Material();
  m.setPattern(std::make_shared<StripePattern>(StripePattern(Color(1, 1, 1), Color(0, 0, 0))));
  m.setAmbient(1);
  m.setDiffuse(0);
  m.setSpecular(0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 0, -10), Color(1, 1, 1));

  Sphere obj;
  Color c1 = m.lighting(&obj, light, Tuple::create_point(0.9, 0, 0), eyev, normalv, false);
  Color c2 = m.lighting(&obj, light, Tuple::create_point(1.1, 0, 0), eyev, normalv, false);

  REQUIRE (c1 == Color(1, 1, 1));
  REQUIRE (c2 == Color(0, 0, 0));
}

TEST_CASE("Stripes with an object transformation", "[transformation]") {
  Color white = Color(1, 1, 1);
  Color black = Color(0, 0, 0);

  Sphere object = Sphere();
  object.setTransform(Matrix::scaling(2, 2, 2));
  StripePattern pattern = StripePattern(white, black);
  Color c = pattern.pattern_at_shape(&object, Tuple::create_point(1.5, 0, 0));

  REQUIRE (c == white);
}

TEST_CASE("Stripes with a pattern transformation", "[transformation]") {
  Color white = Color(1, 1, 1);
  Color black = Color(0, 0, 0);
  Sphere object = Sphere();
  StripePattern pattern = StripePattern(white, black);

  pattern.set_transform(Matrix::scaling(2, 2, 2));

  Color c = pattern.pattern_at_shape(&object, Tuple::create_point(1.5, 0, 0));

  REQUIRE (c == white);
}

TEST_CASE("Stripes with both an object and a pattern transformation", "[transformation]") {
  Color white = Color(1, 1, 1);
  Color black = Color(0, 0, 0);
  StripePattern pattern = StripePattern(white, black);
  Sphere object = Sphere();
  object.setTransform(Matrix::scaling(2, 2, 2));

  pattern.set_transform(Matrix::translation(0.5, 0, 0));
  Color c = pattern.pattern_at_shape(&object, Tuple::create_point(2.5, 0, 0));

  REQUIRE (c == white);
}

TEST_CASE ("The default pattern transformation", "[test_pattern]") {
  TestPattern pattern = TestPattern();
  REQUIRE (pattern.transform() == Matrix::identity_matrix(4));
}

TEST_CASE ("Assigning a transformation test pattern", "[test_pattern]") {
  TestPattern pattern = TestPattern();
  pattern.set_transform(Matrix::translation(1, 2, 3));
  REQUIRE (pattern.transform() == Matrix::translation(1, 2, 3));
}

TEST_CASE ("A pattern with an object transformation", "[test_pattern]") {
  Sphere shape = Sphere();
  shape.setTransform(Matrix::scaling(2, 2, 2));

  TestPattern pattern = TestPattern();

  Color c = pattern.pattern_at_shape(&shape, Tuple::create_point(2, 3, 4));
  REQUIRE (c == Color(1, 1.5, 2));
}

TEST_CASE ("A pattern with an pattern transformation", "[test_pattern]") {
  Sphere shape = Sphere();

  TestPattern pattern = TestPattern();
  pattern.set_transform(Matrix::scaling(2, 2, 2));

  Color c = pattern.pattern_at_shape(&shape, Tuple::create_point(2, 3, 4));
  REQUIRE (c == Color(1, 1.5, 2));
}

TEST_CASE ("A pattern with both an object and pattern transformation", "[test_pattern]") {
  Sphere shape = Sphere();
  shape.setTransform(Matrix::scaling(2, 2, 2));

  TestPattern pattern = TestPattern();
  pattern.set_transform(Matrix::translation(0.5, 1, 1.5));

  Color c = pattern.pattern_at_shape(&shape, Tuple::create_point(2.5, 3, 3.5));
  REQUIRE (c == Color(0.75, 0.5, 0.25));
}

TEST_CASE ("A gradient linearly interpolates between colors", "[gradient]") {
  Gradient pattern = Gradient(Color(1, 1, 1), Color(0, 0, 0));

  REQUIRE(pattern.pattern_at(Tuple::create_point(0, 0, 0)) == Color(1, 1, 1));
  REQUIRE(pattern.pattern_at(Tuple::create_point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
  REQUIRE(pattern.pattern_at(Tuple::create_point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
  REQUIRE(pattern.pattern_at(Tuple::create_point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));
}
