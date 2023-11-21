#include <catch2/catch.hpp>

#include "../src/primitives/tuple.hpp"
#include "../src/shapes/triangle.hpp"


TEST_CASE("Constructing a triangle", "[triangle]") {
  auto p1 = Tuple::create_point(0, 1, 0);
  auto p2 = Tuple::create_point(-1, 0, 0);
  auto p3 = Tuple::create_point(1, 0, 0);

  auto t = Triangle(p1, p2, p3);

  REQUIRE (t.p1() == p1);
  REQUIRE (t.p2() == p2);
  REQUIRE (t.p3() == p3);

  REQUIRE (t.e1() == Tuple::create_vector(-1, -1, 0));
  REQUIRE (t.e2() == Tuple::create_vector(1, -1, 0));

  REQUIRE (t.normal() == Tuple::create_vector(0, 0, -1));
}
