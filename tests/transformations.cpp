#include <catch2/catch.hpp>

#include "../src/matrix.hpp"
#include "../src/tuple.hpp"

TEST_CASE ( "Multiplying by a translation matrix", "[matrices]" ) {
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

TEST_CASE ( "A scaling matrix applied to a point", "[matrices]" ) {
  Matrix t = Matrix::scaling(2, 3, 4);
  Tuple p = Tuple::create_point(-4, 6, 8);
  REQUIRE ( t * p == Tuple::create_point(-8, 18, 32) );
}

TEST_CASE ( "A scaling matrix applied to a vector", "[matrices]" ) {
  Matrix t = Matrix::scaling(2, 3, 4);
  Tuple p = Tuple::create_vector(-4, 6, 8);
  REQUIRE ( t * p == Tuple::create_vector(-8, 18, 32) );
}

TEST_CASE ( "Multiplying by the inverse of a scaling matrix", "[matrices]" ) {
  Matrix t = Matrix::scaling(2, 3, 4);
  Matrix inv = t.inverse();
  Tuple p = Tuple::create_vector(-4, 6, 8);
  REQUIRE ( inv * p == Tuple::create_vector(-2, 2, 2) );
}

TEST_CASE ( "Reflection is scaling by a negative value", "[matrices]" ) {
  Matrix t = Matrix::scaling(-1, 1, 1);
  Tuple p = Tuple::create_point(2, 3, 4);
  REQUIRE ( t * p == Tuple::create_point(-2, 3, 4) );
}
