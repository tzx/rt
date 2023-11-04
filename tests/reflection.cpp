#include <catch2/catch.hpp>
#include <cmath>

#include "../src/lights/material.hpp"
#include "../src/shapes/plane.hpp"
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
