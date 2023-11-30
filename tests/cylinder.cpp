#include <catch2/catch.hpp>
#include <iostream>
#include <limits>
#include <memory>

#include "../src/shapes/cylinder.hpp"
#include "../src/primitives/tuple.hpp"
#include "../src/intersections/ray.hpp"

TEST_CASE("A ray misses a cylinder", "[cylinder]") {
  auto cyl = Cylinder();

  std::vector<Tuple> directions = { Tuple::create_vector(0, 1, 0), Tuple::create_vector(0, 1, 0), Tuple::create_vector(1, 1, 1) };
  std::vector<Tuple> origins = { Tuple::create_point(1, 0, 0), Tuple::create_point(0, 0, 0), Tuple::create_point(0, 0, -5) };

  REQUIRE (directions.size() == origins.size());
  auto size = directions.size();

  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i);
    auto origin = origins.at(i);
    auto r = Ray(origin, direction);
    auto xs = cyl.local_intersect(r);

    REQUIRE (xs.empty());
  }
}

TEST_CASE("A ray strikes a cylinder", "[cylinder]") {
  auto cyl = std::make_shared<Cylinder>();

  std::vector<Tuple> directions = { Tuple::create_vector(0, 0, 1),
                                    Tuple::create_vector(0, 0, 1),
                                    Tuple::create_vector(0.1, 1, 1) };
  std::vector<Tuple> origins = { Tuple::create_point(1, 0, -5),
                                 Tuple::create_point(0, 0, -5),
                                 Tuple::create_point(0.5, 0, -5) };
  std::vector<float> t0s = { 5,
                             4,
                             6.80798 };
  std::vector<float> t1s = { 5,
                             6,
                             7.08872 };
  auto size = 3;

  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i).getNormalized();
    auto r = Ray(origins.at(i), direction);
    auto t0 = t0s.at(i);
    auto t1 = t1s.at(i);

    auto xs = cyl->local_intersect(r);
    REQUIRE (xs.size() == 2);

    REQUIRE (xs.at(0).t() == Approx(t0));
    REQUIRE (xs.at(1).t() == Approx(t1));
  }
}

TEST_CASE("Normal vector on a cylinder", "[cylinder]") {
  auto cyl = std::make_shared<Cylinder>();

  std::vector<Tuple> points = { Tuple::create_point(1, 0, 0),
                                Tuple::create_point(0, 5, -1),
                                Tuple::create_point(0, -2, 1),
                                Tuple::create_point(-1, 1, 0)};
  std::vector<Tuple> normals = { Tuple::create_vector(1, 0, 0),
                                 Tuple::create_vector(0, 0, -1),
                                 Tuple::create_vector(0, 0, 1),
                                 Tuple::create_vector(-1, 0, 0) };
  auto size = 4;

  for (auto i = 0; i < size; ++i) {
    auto point = points.at(i);
    auto normal = normals.at(i);

    auto n = cyl->local_normal_at(point);

    REQUIRE (n == normal);
  }
}

TEST_CASE("The default minimum and maximum for a cylinder", "[cylinder]") {
  auto cyl = Cylinder();
  REQUIRE (cyl.minimum() == std::numeric_limits<float>::lowest());
  REQUIRE (cyl.maximum() == std::numeric_limits<float>::max());
}

TEST_CASE ("Intersecting a constrained cylinder", "[cylinder]") {
  auto cyl = std::make_shared<Cylinder>();
  cyl->set_minimum(1);
  cyl->set_maximum(2);

  std::vector<Tuple> points = { Tuple::create_point(0, 1.5, 0),
                                Tuple::create_point(0, 3, -5),
                                Tuple::create_point(0, 0, -5),
                                Tuple::create_point(0, 2, -5),
                                Tuple::create_point(0, 1, -5),
                                Tuple::create_point(0, 1.5, -2)};
  std::vector<Tuple> directions = { Tuple::create_vector(0.1, 1, 0),
                                 Tuple::create_vector(0, 0, 1),
                                 Tuple::create_vector(0, 0, 1),
                                 Tuple::create_vector(0, 0, 1),
                                 Tuple::create_vector(0, 0, 1),
                                 Tuple::create_vector(0, 0, 1)};
  std::vector<size_t> counts = {0,
                                0,
                                0,
                                0,
                                0,
                                2};

  auto size = 6;
  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i).getNormalized();
    auto r = Ray(points.at(i), direction);
    auto xs = cyl->local_intersect(r);
    REQUIRE (xs.size() == counts.at(i));
  }
}

TEST_CASE ("The default closed value for a cylinder", "[cylinder]") {
  auto cyl = Cylinder();
  REQUIRE_FALSE (cyl.closed());
}

TEST_CASE ("Intersecting the caps of a closed cylinder", "[cylinder]") {
  auto cyl = std::make_shared<Cylinder>();
  cyl->set_minimum(1);
  cyl->set_maximum(2);
  cyl->set_closed(true);

  std::vector<Tuple> points = { Tuple::create_point(0, 3, 0),
                                Tuple::create_point(0, 3, -2),
                                Tuple::create_point(0, 4, -2),
                                Tuple::create_point(0, 0, -2),
                                Tuple::create_point(0, -1, -2)};
  std::vector<Tuple> directions = { Tuple::create_vector(0, -1, 0),
                                    Tuple::create_vector(0, -1, 2),
                                    Tuple::create_vector(0, -1, 1),
                                    Tuple::create_vector(0, 1, 2),
                                    Tuple::create_vector(0, 1, 1)};
  std::vector<size_t> counts = {2,
                                2,
                                2,
                                2,
                                2};
  // idx 2, 4 are the corner cases
  auto size = 5;
  for (auto i = 0; i < size; ++i) {
    auto direction = directions.at(i).getNormalized();
    auto r = Ray(points.at(i), direction);
    auto xs = cyl->local_intersect(r);
    REQUIRE (xs.size() == counts.at(i));
  }
}

TEST_CASE ("The normal vector on a cylinder's end caps", "[cylinder]") {
  auto cyl = std::make_shared<Cylinder>();
  cyl->set_minimum(1);
  cyl->set_maximum(2);
  cyl->set_closed(true);

  std::vector<Tuple> points = { Tuple::create_point(0, 1, 0),
                                Tuple::create_point(0.5, 1, 0),
                                Tuple::create_point(0, 1, 0.5),
                                Tuple::create_point(0, 2, 0),
                                Tuple::create_point(0.5, 2, 0),
                                Tuple::create_point(0, 2, 0.5)};
  std::vector<Tuple> normals = { Tuple::create_vector(0, -1, 0),
                                    Tuple::create_vector(0, -1, 0),
                                    Tuple::create_vector(0, -1, 0),
                                    Tuple::create_vector(0, 1, 0),
                                    Tuple::create_vector(0, 1, 0),
                                    Tuple::create_vector(0, 1, 0)};
  
  auto size = 6;
  for (auto i = 0; i < size; ++i) {
    auto n = cyl->local_normal_at(points.at(i));
    REQUIRE (n == normals.at(i));
  }
}
