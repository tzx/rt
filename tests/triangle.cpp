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

TEST_CASE("Finding the normal on a triangle", "[triangle]") {
  auto t = Triangle(Tuple::create_point(0, 1, 0),
                    Tuple::create_point(-1, 0, 0), 
                    Tuple::create_point(1, 0, 0));

  auto n1 = t.local_normal_at(Tuple::create_point(0, 0.5, 0));
  auto n2 = t.local_normal_at(Tuple::create_point(-0.5, 0.75, 0));
  auto n3 = t.local_normal_at(Tuple::create_point(0.5, 0.25, 0));

  REQUIRE (n1 == t.normal());
  REQUIRE (n2 == t.normal());
  REQUIRE (n3 == t.normal());
}

TEST_CASE("Intersecting a ray parallel to the triangle", "[triangle]") {
  auto t = Triangle(Tuple::create_point(0, 1, 0),
                    Tuple::create_point(-1, 0, 0), 
                    Tuple::create_point(1, 0, 0));
  auto r = Ray(Tuple::create_point(0, -1, 2), Tuple::create_vector(0, 1, 0));

  auto xs = t.local_intersect(r);

  REQUIRE (xs.empty());
}

TEST_CASE("A ray misses the p1-p3 edge", "[triangle]") {
  auto t = Triangle(Tuple::create_point(0, 1, 0),
                    Tuple::create_point(-1, 0, 0), 
                    Tuple::create_point(1, 0, 0));
  auto r = Ray(Tuple::create_point(1, 1, -2), Tuple::create_vector(0, 0, 1));
  auto xs = t.local_intersect(r);

  REQUIRE (xs.empty());
}

TEST_CASE("A ray misses the p1-p2 edge", "[triangle]") {
  auto t = Triangle(Tuple::create_point(0, 1, 0),
                    Tuple::create_point(-1, 0, 0), 
                    Tuple::create_point(1, 0, 0));
  auto r = Ray(Tuple::create_point(-1, 1, -2), Tuple::create_vector(0, 0, 1));
  auto xs = t.local_intersect(r);

  REQUIRE (xs.empty());
}

TEST_CASE("A ray misses the p2-p3 edge", "[triangle]") {
  auto t = Triangle(Tuple::create_point(0, 1, 0),
                    Tuple::create_point(-1, 0, 0), 
                    Tuple::create_point(1, 0, 0));
  auto r = Ray(Tuple::create_point(0, -1, -2), Tuple::create_vector(0, 0, 1));
  auto xs = t.local_intersect(r);

  REQUIRE (xs.empty());
}

TEST_CASE("A ray strikes a triangle", "[triangle]") {
  auto t = std::make_shared<Triangle>(Tuple::create_point(0, 1, 0),
                                      Tuple::create_point(-1, 0, 0), 
                                      Tuple::create_point(1, 0, 0));
  auto r = Ray(Tuple::create_point(0, 0.5, -2), Tuple::create_vector(0, 0, 1));
  auto xs = t->local_intersect(r);

  REQUIRE (xs.size() == 1);
  REQUIRE (xs.at(0).t() == 2);
}
