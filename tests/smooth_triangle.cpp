#include <catch2/catch.hpp>

#include "../src/primitives/tuple.hpp"
#include "../src/shapes/smooth_triangle.hpp"
#include "../src/shapes/triangle.hpp"

TEST_CASE("Constructing a smooth triangle", "[smooth triangle]") {
  auto p1 = Tuple::create_point(0, 1, 0);
  auto p2 = Tuple::create_point(-1, 0, 0);
  auto p3 = Tuple::create_point(1, 0, 0);

  auto n1 = Tuple::create_vector(0, 1, 0);
  auto n2 = Tuple::create_vector(-1, 0, 0);
  auto n3 = Tuple::create_vector(1, 0, 0);

  auto tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);

  REQUIRE(tri.p1() == p1);
  REQUIRE(tri.p2() == p2);
  REQUIRE(tri.p3() == p3);
  REQUIRE(tri.n1() == n1);
  REQUIRE(tri.n2() == n2);
  REQUIRE(tri.n3() == n3);
}

// TEST_CASE("An intersection can encapsulate `u` and `v`", "[smooth triangle]") {
//   auto s = Triangle(Tuple::create_point(0, 1, 0), Tuple::create_point(-1, 0, 0),
//                     Tuple::create_point(1, 0, 0));
//   auto i = IntersectionUV(3.5, s, 0.2, 0.4);
//   REQUIRE (i.u() == 0.2);
//   REQUIRE (i.v() == 0.4);
// }

// TEST_CASE("An intersection with a smooth triangle stores u/v", "[smooth triangle]") {
//   auto p1 = Tuple::create_point(0, 1, 0);
//   auto p2 = Tuple::create_point(-1, 0, 0);
//   auto p3 = Tuple::create_point(1, 0, 0);
// 
//   auto n1 = Tuple::create_vector(0, 1, 0);
//   auto n2 = Tuple::create_vector(-1, 0, 0);
//   auto n3 = Tuple::create_vector(1, 0, 0);
// 
//   auto tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
// 
//   auto r = Ray(Tuple::create_point(-0.2, 0.3, -2), Tuple::create_vector(0, 0, 1));
//   auto xs = tri.local_intersect(r);
//   REQUIRE (xs.at(0).u() == Approx(0.45));
//   REQUIRE (xs.at(0).v() == Approx(0.25));
// }
