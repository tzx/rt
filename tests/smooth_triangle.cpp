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

TEST_CASE("An intersection can encapsulate `u` and `v`", "[smooth triangle]") {
  auto s = std::make_shared<Triangle>(Tuple::create_point(0, 1, 0), Tuple::create_point(-1, 0, 0),
                    Tuple::create_point(1, 0, 0));
  auto i = Intersection(3.5, s, 0.2, 0.4);
  REQUIRE (i.u() == Approx(0.2));
  REQUIRE (i.v() == Approx(0.4));
}

TEST_CASE("An intersection with a smooth triangle stores u/v", "[smooth triangle]") {
  auto p1 = Tuple::create_point(0, 1, 0);
  auto p2 = Tuple::create_point(-1, 0, 0);
  auto p3 = Tuple::create_point(1, 0, 0);

  auto n1 = Tuple::create_vector(0, 1, 0);
  auto n2 = Tuple::create_vector(-1, 0, 0);
  auto n3 = Tuple::create_vector(1, 0, 0);

  auto tri = std::make_shared<SmoothTriangle>(p1, p2, p3, n1, n2, n3);

  auto r = Ray(Tuple::create_point(-0.2, 0.3, -2), Tuple::create_vector(0, 0, 1));
  auto xs = tri->local_intersect(r);
  REQUIRE (xs.at(0).u() == Approx(0.45));
  REQUIRE (xs.at(0).v() == Approx(0.25));
}

TEST_CASE("A smooth triangle uses u/v to interpolate the normal", "[smooth triangle]") {
  auto p1 = Tuple::create_point(0, 1, 0);
  auto p2 = Tuple::create_point(-1, 0, 0);
  auto p3 = Tuple::create_point(1, 0, 0);

  auto n1 = Tuple::create_vector(0, 1, 0);
  auto n2 = Tuple::create_vector(-1, 0, 0);
  auto n3 = Tuple::create_vector(1, 0, 0);

  auto tri = std::make_shared<SmoothTriangle>(p1, p2, p3, n1, n2, n3);

  auto i = Intersection(1, tri, 0.45, 0.25);
  auto n = tri->normal_at(Tuple::create_point(0, 0, 0), i);
  REQUIRE(n == Tuple::create_vector(-0.5547, 0.83205, 0));
}

TEST_CASE("Preparing the normal on a smooth triangle", "[smooth triangle]") {
  auto p1 = Tuple::create_point(0, 1, 0);
  auto p2 = Tuple::create_point(-1, 0, 0);
  auto p3 = Tuple::create_point(1, 0, 0);

  auto n1 = Tuple::create_vector(0, 1, 0);
  auto n2 = Tuple::create_vector(-1, 0, 0);
  auto n3 = Tuple::create_vector(1, 0, 0);

  auto tri = std::make_shared<SmoothTriangle>(p1, p2, p3, n1, n2, n3);

  auto i = Intersection(1, tri, 0.45, 0.25);
  auto r = Ray(Tuple::create_point(-0.2, 0.3, -2), Tuple::create_vector(0, 0, 1));
  std::vector<Intersection> xs = { i };
  auto comps = Computations(i, r, xs);
  comps.normalv().repr();
  REQUIRE (comps.normalv() == Tuple::create_vector(-0.5547, 0.83205, 0));
}
