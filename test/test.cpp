#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

#include "../src/tuple.hpp"

TEST_CASE( "Point is point with right coordinates", "[point]" ) {
  Tuple p = Tuple::create_point(1, 2, 3);
  REQUIRE( p.getX() == Approx(1) );
  REQUIRE( p.getY() == Approx(2) );
  REQUIRE( p.getZ() == Approx(3) );
  REQUIRE( p.getW() == Approx(0) );
}

TEST_CASE( "Vector is vector with right coordinates", "[vector]" ) {
  Tuple v = Tuple::create_vector(78.1, 29, 88.333);
  REQUIRE( v.getX() == Approx(78.1) );
  REQUIRE( v.getY() == Approx(29) );
  REQUIRE( v.getZ() == Approx(88.333) );
  REQUIRE( v.getW() == Approx(1) );
}
