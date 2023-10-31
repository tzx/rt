#include <catch2/catch.hpp>

#include "../src/ray.hpp"

TEST_CASE ("Creating and querying a ray", "[ray]") {
  Tuple origin = Tuple::create_point(1, 2, 3);
  Tuple direction = Tuple::create_vector(4, 5, 6);

  Ray ray = Ray(origin, direction);

  REQUIRE(ray.origin() == origin);
  REQUIRE(ray.direction() == direction);
}

TEST_CASE ("Computing a point from a distance", "[ray]") {
  Ray ray = Ray(Tuple::create_point(2, 3, 4), Tuple::create_vector(1, 0, 0));

  REQUIRE(ray.position(0) == Tuple::create_point(2, 3, 4));
  REQUIRE(ray.position(1) == Tuple::create_point(3, 3, 4));
  REQUIRE(ray.position(-1) == Tuple::create_point(1, 3, 4));
  REQUIRE(ray.position(2.5) == Tuple::create_point(4.5, 3, 4));
}
