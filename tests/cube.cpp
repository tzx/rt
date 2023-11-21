#include <catch2/catch.hpp>

#include "../src/primitives/tuple.hpp"
#include "../src/shapes/cube.hpp"
#include "../src/ray.hpp"

TEST_CASE("A ray intersects a cube", "[cube]") {
  auto c = std::make_shared<Cube>();

  std::vector<Tuple> origins = {
    Tuple::create_point(5, 0.5, 0),
    Tuple::create_point(-5, 0.5, 0),
    Tuple::create_point(0.5, 5, 0),
    Tuple::create_point(0.5, -5, 0),
    Tuple::create_point(0.5, 0, 5),
    Tuple::create_point(0.5, 0, -5),
    Tuple::create_point(0, 0.5, 0)
  };

  std::vector<Tuple> directions = {
    Tuple::create_vector(-1, 0, 0),
    Tuple::create_vector(1, 0, 0),
    Tuple::create_vector(0, -1, 0),
    Tuple::create_vector(0, 1, 0),
    Tuple::create_vector(0, 0, -1),
    Tuple::create_vector(0, 0, 1),
    Tuple::create_vector(0, 0, 1)
  };

  std::vector<float> t1s = {
    4,
    4,
    4,
    4,
    4,
    4,
    1,
  };

  std::vector<float> t2s = {
    6,
    6,
    6,
    6,
    6,
    6,
    1,
  };

  auto size = 6;
  for (auto i = 0; i < size; ++i) {
    auto r = Ray(origins.at(i), directions.at(i));
    auto xs = c->local_intersect(r);
    REQUIRE (xs.size() == 2);
    REQUIRE (xs.at(0).t() == t1s.at(i));
    REQUIRE (xs.at(1).t() == t2s.at(i));
  }
}
