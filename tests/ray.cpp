#include <catch2/catch.hpp>
#include <iostream>

#include "../src/ray.hpp"
#include "../src/sphere.hpp"
#include "../src/intersection.hpp"

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

TEST_CASE ("A ray intersects a sphere at two points", "[intersection]") {
  Ray ray = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, ray);
  REQUIRE( xs.size() == 2 );
  REQUIRE( xs[0].t() == Approx(4.0) );
  REQUIRE( xs[1].t() == Approx(6.0) );
}


TEST_CASE ("A ray intersects a sphere at a tangent", "[intersection]") {
  Ray ray = Ray(Tuple::create_point(0, 1, -5), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, ray);
  REQUIRE( xs.size() == 2 );
  REQUIRE( xs[0].t() == Approx(5.0) );
  REQUIRE( xs[1].t() == Approx(5.0) );
}

TEST_CASE ("A ray misses a sphere", "[intersection]") {
  Ray ray = Ray(Tuple::create_point(0, 2, -5), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, ray);
  REQUIRE( xs.size() == 0 );
}

TEST_CASE ("A ray originates inside a sphere", "[intersection]") {
  Ray ray = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, ray);
  REQUIRE( xs.size() == 2 );
  REQUIRE( xs[0].t() == Approx(-1.0) );
  REQUIRE( xs[1].t() == Approx(1.0) );
}

TEST_CASE ("A sphere is behind a ray", "[intersection]") {
  Ray ray = Ray(Tuple::create_point(0, 0, 5), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, ray);
  REQUIRE( xs.size() == 2 );
  REQUIRE( xs[0].t() == Approx(-6.0) );
  REQUIRE( xs[1].t() == Approx(-4.0) );
}

TEST_CASE ("A intersection encapsulates t and object", "[intersection]") {
  Sphere s = Sphere();

  Intersection i = Intersection(3.5, s);

  REQUIRE ( i.t() == Approx(3.5) );
  REQUIRE ( i.object() == s );
}

TEST_CASE ("Aggregating intersections", "[intersection]") {
  Sphere s = Sphere();

  Intersection i1 = Intersection(1, s);
  Intersection i2 = Intersection(2, s);

  std::vector<Intersection> xs = {i1, i2};

  REQUIRE ( xs.size() == 2 );
  REQUIRE ( xs[0].t() == 1 );
  REQUIRE ( xs[1].t() == 2 );
}

TEST_CASE ("Intersect sets the object on the intersection", "[intersection]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  Sphere s = Sphere();

  std::vector<Intersection> xs = intersect(s, r);

  REQUIRE ( xs.size() == 2 );
  REQUIRE ( xs[0].object() == s );
  REQUIRE ( xs[1].object() == s );
}

TEST_CASE ("The hit, when all intersections have positive t", "[hit]") {
  Sphere s = Sphere();
  Intersection i1 = Intersection(1, s);
  Intersection i2 = Intersection(2, s);
  std::vector<Intersection> xs = {i1, i2};

  auto i = hit(xs);
  REQUIRE( i1 == i.value() );
}

TEST_CASE ("The hit, when some intersection have negative t", "[hit]") {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-1, s);
  Intersection i2 = Intersection(1, s);
  std::vector<Intersection> xs = {i2, i1};

  auto i = hit(xs);
  REQUIRE( i2 == i.value() );
}

TEST_CASE ("The hit, when all intersections have negative t", "[hit]") {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-2, s);
  Intersection i2 = Intersection(-1, s);
  std::vector<Intersection> xs = {i2, i1};

  auto i = hit(xs);
  REQUIRE_FALSE( i.has_value() );
}

TEST_CASE ("The hit is always the lowest nonnegative intersection", "[hit]") {
  Sphere s = Sphere();
  Intersection i1 = Intersection(5, s);
  Intersection i2 = Intersection(7, s);
  Intersection i3 = Intersection(-3, s);
  Intersection i4 = Intersection(2, s);
  std::vector<Intersection> xs = {i1, i2, i3, i4};

  auto i = hit(xs);
  REQUIRE( i.value() == i4 );
}
