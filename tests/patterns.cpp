#include <catch2/catch.hpp>

#include "../src/canvas/color.hpp"
#include "../src/patterns/stripe_pattern.hpp"
#include "../src/lights/material.hpp"

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
  
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 1, 0)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 2, 0)) == white);
}

TEST_CASE("A stripe pattern is constant in z", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 0, 1)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 0, 2)) == white);
}

TEST_CASE("A stripe pattern alternates in x", "[pattern]") {
  Color black = Color(0, 0, 0);
  Color white = Color(1, 1, 1);

  StripePattern pattern = StripePattern(white, black);
  
  REQUIRE(pattern.stripe_at(Tuple::create_point(0, 0, 0)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(0.9, 0, 0)) == white);
  REQUIRE(pattern.stripe_at(Tuple::create_point(1, 0, 0)) == black);
  REQUIRE(pattern.stripe_at(Tuple::create_point(-0.1, 0, 0)) == black);
  REQUIRE(pattern.stripe_at(Tuple::create_point(-1, 0, 0)) == black);
  REQUIRE(pattern.stripe_at(Tuple::create_point(-1.1, 0, 0)) == white);
}

TEST_CASE("Lighting with a pattern applied", "[material]") {
  Material m = Material();
  m.setPattern(StripePattern(Color(1, 1, 1), Color(0, 0, 0)));
  m.setAmbient(1);
  m.setDiffuse(0);
  m.setSpecular(0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 0, -10), Color(1, 1, 1));

  Color c1 = m.lighting(light, Tuple::create_point(0.9, 0, 0), eyev, normalv, false);
  Color c2 = m.lighting(light, Tuple::create_point(1.1, 0, 0), eyev, normalv, false);

  REQUIRE (c1 == Color(1, 1, 1));
  REQUIRE (c2 == Color(0, 0, 0));
}
