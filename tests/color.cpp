#include <catch2/catch.hpp>

#include "../src/color.hpp"

TEST_CASE ( "Colors are tuples", "[color]" ) {
  Color c = Color(-0.5, 0.4, 1.7);
  REQUIRE( c.r() == Approx(-0.5) );
  REQUIRE( c.g() == Approx(0.4) );
  REQUIRE( c.b() == Approx(1.7) );
}

TEST_CASE ( "Color operations plus and minus", "[color]" ) {
  Color c1 = Color(0.9, 0.6, 0.75);
  Color c2 = Color(0.7, 0.1, 0.25);

  Color sum = c1 + c2;
  REQUIRE( sum.r() == Approx(1.6) );
  REQUIRE( sum.g() == Approx(0.7) );
  REQUIRE( sum.b() == Approx(1.0) );

  Color diff = c1 - c2;
  REQUIRE( diff.r() == Approx(0.2) );
  REQUIRE( diff.g() == Approx(0.5) );
  REQUIRE( diff.b() == Approx(0.5) );

}

TEST_CASE ( "Color operations: scalar multiplication", "[color]" ) {
  Color c = Color(0.2, 0.3, 0.4);
  Color scal_prod = c * 2;
  REQUIRE( scal_prod.r() == Approx(0.4) );
  REQUIRE( scal_prod.g() == Approx(0.6) );
  REQUIRE( scal_prod.b() == Approx(0.8) );
}

TEST_CASE ( "Color operations: hadamard product", "[color]" ) {
  Color c1 = Color(1, 0.2, 0.4);
  Color c2 = Color(0.9, 1, 0.1);
  Color prod = c1 * c2;
  REQUIRE( prod.r() == Approx(0.9) );
  REQUIRE( prod.g() == Approx(0.2) );
  REQUIRE( prod.b() == Approx(0.04) );
}
