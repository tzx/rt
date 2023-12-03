#include <catch2/catch.hpp>
#include <limits>

#include "../src/shapes/bounds.hpp"

TEST_CASE("Merging two bounds combines well", "[bounds]") {
  auto b1 = Bounds(Tuple::create_point(-1, 0, -1), Tuple::create_point(1, 0, 1));
  auto b2 = Bounds(Tuple::create_point(-std::numeric_limits<float>::infinity(), -1, 0), Tuple::create_point(std::numeric_limits<float>::infinity(), 1, 0));
  b1.merge(b2);

  REQUIRE (b1 == Bounds(Tuple::create_point(-std::numeric_limits<float>::infinity(), -1, -1),
                        Tuple::create_point(std::numeric_limits<float>::infinity(), 1, 1)));
}

TEST_CASE("Rotation by 45 deg on bounding box", "[bounds]") {
  auto bounds = Bounds(Tuple::create_point(-1, -1, -1), Tuple::create_point(1, 1, 1));
  bounds.transform(Mat4::rotation_y(M_PI_4f));

  REQUIRE (bounds == Bounds(Tuple::create_point(-std::sqrt(2), -1, -std::sqrt(2)),
                        Tuple::create_point(std::sqrt(2), 1, std::sqrt(2))));
}
