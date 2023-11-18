#include <catch2/catch.hpp>
#include <iostream>

#include "../src/shapes/cylinder.hpp"
#include "../src/primitives/tuple.hpp"
#include "../src/ray.hpp"

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
