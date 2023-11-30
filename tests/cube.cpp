#include <catch2/catch.hpp>

#include "../src/primitives/tuple.hpp"
#include "../src/shapes/cube.hpp"
#include "../src/intersections/ray.hpp"

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

TEST_CASE("A ray misses a cube", "[cube]") {
  // TODO: I just realized, can we enforce that shapes must be a shared_ptr
  auto c = std::make_shared<Cube>();

  std::vector<Tuple> origins = {
    Tuple::create_point(-2, 0, 0),
    Tuple::create_point(0, -2, 0),
    Tuple::create_point(0, 0, -2),
    Tuple::create_point(2, 0, 2),
    Tuple::create_point(0, 2, 2),
    Tuple::create_point(2, 2, 0)
  };

  std::vector<Tuple> directions = {
    Tuple::create_vector(0.2673, 0.5345, 0.8018),
    Tuple::create_vector(0.8018, 0.2673, 0.5345),
    Tuple::create_vector(0.5345, 0.8018, 0.2673),
    Tuple::create_vector(0, 0, -1),
    Tuple::create_vector(0, -1, 0),
    Tuple::create_vector(-1, 0, 0)
  };

  auto size = 6;
  for (auto i = 0; i < size; ++i) {
    auto r = Ray(origins.at(i), directions.at(i));
    auto xs = c->local_intersect(r);
    REQUIRE (xs.empty());
  }
}

TEST_CASE("The normal on the surface of a cube", "[cube]") {
  auto c = std::make_shared<Cube>();

  std::vector<Tuple> points = {
    Tuple::create_point(1, 0.5, -0.8),
    Tuple::create_point(-1, -0.2, 0.9),
    Tuple::create_point(-0.4, 1, -0.1),
    Tuple::create_point(0.3, -1, -0.7),
    Tuple::create_point(-0.6, 0.3, 1),
    Tuple::create_point(0.4, 0.4, -1),
    Tuple::create_point(1, 1, 1),
    Tuple::create_point(-1, -1, -1),
  };

  std::vector<Tuple> normals = {
    Tuple::create_vector(1, 0, 0),
    Tuple::create_vector(-1, 0, 0),
    Tuple::create_vector(0, 1, 0),
    Tuple::create_vector(0, -1, 0),
    Tuple::create_vector(0, 0, 1),
    Tuple::create_vector(0, 0, -1),
    Tuple::create_vector(1, 0, 0),
    Tuple::create_vector(-1, 0, 0),
  };

  auto size = 8;
  for (auto i = 0; i < size; ++i) {
    auto p = points.at(i);
    auto normal = c->local_normal_at(p);
    REQUIRE (normal == normals.at(i));
  }
}
