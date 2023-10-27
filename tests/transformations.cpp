#include <catch2/catch.hpp>

#include "../src/matrix.hpp"
#include "../src/tuple.hpp"

TEST_CASE( "Multiplying by a translation matrix", "[matrices]" ) {
  Matrix t = Matrix::translation(5, -3, 2);
  Tuple p = Tuple::create_point(-3, 4, 5);

  REQUIRE( t * p == Tuple::create_point(2, 1, 7) );
}

TEST_CASE ( "Multiplying by the inverse of a translation matrix", "[matrices]" ) {
  Matrix t = Matrix::translation(5, -3, 2);
  Matrix inv = t.inverse();
  Tuple p = Tuple::create_point(-3, 4, 5);
  REQUIRE( inv * p == Tuple::create_point(-8, 7, 3) );
}

TEST_CASE ( "Translation does not affect vectors", "[matrices]" ) {
  Matrix t = Matrix::translation(5, -3, 2);
  Tuple v = Tuple::create_vector(-3, 4, 5);
  REQUIRE( t * v == v );
}
