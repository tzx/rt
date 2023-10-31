#include <catch2/catch.hpp>

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
