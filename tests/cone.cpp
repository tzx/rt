#include <catch2/catch.hpp>
#include <iostream>
#include <memory>
#include "../src/primitives/tuple.hpp"
#include "../src/intersections/ray.hpp"
#include "../src/shapes/cone.hpp"

TEST_CASE("Intersecting a cone with a ray", "[cone]") {
  auto shape = std::make_shared<Cone>();

  std::vector<Tuple> origins = {
                                Tuple::create_point(0, 0, -5),
                                Tuple::create_point(0, 0, -5),
                                Tuple::create_point(1, 1, -5)
                               };
  std::vector<Tuple> directions = {
                                Tuple::create_vector(0, 0, 1),
                                Tuple::create_vector(1, 1, 1),
                                Tuple::create_vector(-0.5, -1, 1)
                               };
  std::vector<float> t0s = {
                            5,
                            8.66025,
                            4.55006
                               };
  std::vector<float> t1s = {
                            5,
                            8.66025,
                            49.44994
                               };

  auto size = 3;
  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i).getNormalized();
    auto r = Ray(origins.at(i), direction);
    auto xs = shape->local_intersect(r);

    REQUIRE (xs.size() == 2);
    REQUIRE (xs.at(0).t() == Approx(t0s.at(i)));
    REQUIRE (xs.at(1).t() == Approx(t1s.at(i)));
  }
}

TEST_CASE ("Intersecting a cone with a ray parallel to one of its halves", "[cone]") {
  auto shape = std::make_shared<Cone>();
  auto direction = Tuple::create_vector(0, 1, 1).getNormalized();
  auto r = Ray(Tuple::create_point(0, 0, -1), direction);
  auto xs = shape->local_intersect(r);

  REQUIRE( xs.size() == 1 );
  REQUIRE( xs.at(0).t() == Approx(0.35355) );
}

TEST_CASE ("Intersecting a cone's end caps", "[cone]") {
  auto shape = std::make_shared<Cone>();
  shape->set_minimum(-0.5);
  shape->set_maximum(0.5);
  shape->set_closed(true);

  std::vector<Tuple> origins = {
                                Tuple::create_point(0, 0, -5),
                                Tuple::create_point(0, 0, -0.25),
                                Tuple::create_point(0, 0, -0.25)
                               };
  std::vector<Tuple> directions = {
                                Tuple::create_vector(0, 1, 0),
                                Tuple::create_vector(0, 1, 1),
                                Tuple::create_vector(0, 1, 0)
                               };
  std::vector<size_t> counts = {
                                0,
                                2,
                                4
                               };
  auto size = 3;
  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i).getNormalized();
    auto r = Ray(origins.at(i), direction);
    auto xs = shape->local_intersect(r);

    REQUIRE (xs.size() == counts.at(i));
  }
}

TEST_CASE ("Computing the normal vector on a cone", "[cone]") {
  auto shape = std::make_shared<Cone>();
  std::vector<Tuple> points = {
                                Tuple::create_point(0, 0, 0),
                                Tuple::create_point(1, 1, 1),
                                Tuple::create_point(-1, -1, 0)
                               };
  std::vector<Tuple> normals = {
                                Tuple::create_vector(0, 0, 0),
                                Tuple::create_vector(1, -std::sqrt(2.0), 1),
                                Tuple::create_vector(-1, 1, 0)
                               };
  auto size = 3;
  for (auto i = 0; i < size; ++i) {
    auto n = shape->local_normal_at(points.at(i));
    REQUIRE ( n == normals.at(i) );
  }
}
