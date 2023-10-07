#include <catch2/catch.hpp>

#include "../src/color.hpp"

TEST_CASE ( "Colors are tuples", "[color]" ) {
  Color c = Color(-0.5, 0.4, 1.7);
  REQUIRE( c.r() == Approx(-0.5) );
  REQUIRE( c.g() == Approx(0.4) );
  REQUIRE( c.b() == Approx(1.7) );
}
