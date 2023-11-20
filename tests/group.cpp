#include <catch2/catch.hpp>

#include "../src/shapes/group.hpp"

TEST_CASE("Creating a new group", "[group]") {
  auto g = Group();

  REQUIRE (g.transform() == Matrix::identity_matrix(4));
  REQUIRE (g.shapes().empty());
}
