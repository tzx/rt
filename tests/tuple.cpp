#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../src/tuple.hpp"

TEST_CASE( "Point is point with right coordinates", "[tuple]" ) {
  Tuple p = Tuple::create_point(1, 2, 3);
  REQUIRE( p.getX() == Approx(1) );
  REQUIRE( p.getY() == Approx(2) );
  REQUIRE( p.getZ() == Approx(3) );
  REQUIRE( p.getW() == Approx(1) );
  CHECK( p.isPoint() );
}

TEST_CASE( "Vector is vector with right coordinates", "[tuple]" ) {
  Tuple v = Tuple::create_vector(78.1, 29, 88.333);
  REQUIRE( v.getX() == Approx(78.1) );
  REQUIRE( v.getY() == Approx(29) );
  REQUIRE( v.getZ() == Approx(88.333) );
  REQUIRE( v.getW() == Approx(0) );
  CHECK ( v.isVector() );
}

TEST_CASE( "Adding two tuples", "[tuple]" ) {
  Tuple a1 = Tuple::create_vector(3, -2, 5);
  Tuple a2 = Tuple::create_point(-2, 3, 1);
  Tuple sum = a1 + a2;
  REQUIRE( sum.getX() == Approx(1) );
  REQUIRE( sum.getY() == Approx(1) );
  REQUIRE( sum.getZ() == Approx(6) );
  REQUIRE( sum.getW() == Approx(1) );
  CHECK ( sum.isPoint() );
}

TEST_CASE ("Subtracting two points", "[tuple]" ) {
  Tuple a1 = Tuple::create_point(3, 2, 1);
  Tuple a2 = Tuple::create_point(5, 6, 7);
  Tuple difference = a1 - a2;
  REQUIRE( difference.getX() == Approx(-2) );
  REQUIRE( difference.getY() == Approx(-4) );
  REQUIRE( difference.getZ() == Approx(-6) );
  REQUIRE( difference.getW() == Approx(0) );
  CHECK ( difference.isVector() );
}

TEST_CASE ("Subtracting a vector from a point", "[tuple]" ) {
  Tuple point = Tuple::create_point(3, 2, 1);
  Tuple vector = Tuple::create_vector(5, 6, 7);
  Tuple difference = point - vector;
  REQUIRE( difference.getX() == Approx(-2) );
  REQUIRE( difference.getY() == Approx(-4) );
  REQUIRE( difference.getZ() == Approx(-6) );
  REQUIRE( difference.getW() == Approx(1) );
  CHECK ( difference.isPoint() );
}

TEST_CASE ("Subtracting two vectors", "[tuple]" ) {
  Tuple v1 = Tuple::create_vector(3, 2, 1);
  Tuple v2 = Tuple::create_vector(5, 6, 7);
  Tuple difference = v1 - v2;
  REQUIRE( difference.getX() == Approx(-2) );
  REQUIRE( difference.getY() == Approx(-4) );
  REQUIRE( difference.getZ() == Approx(-6) );
  REQUIRE( difference.getW() == Approx(0) );
  CHECK ( difference.isVector() );
}

TEST_CASE ("Subtracting a vector from a zero vector", "[tuple]" ) {
  Tuple v = Tuple::create_vector(1, -2, 3);
  Tuple zero = Tuple::create_vector(0, 0, 0);
  Tuple difference = zero - v;
  REQUIRE( difference.getX() == Approx(-1) );
  REQUIRE( difference.getY() == Approx(2) );
  REQUIRE( difference.getZ() == Approx(-3) );
  REQUIRE( difference.getW() == Approx(0) );
  CHECK ( difference.isVector() );
}

TEST_CASE ("Negating a tuple", "[tuple]" ) {
  Tuple a = Tuple(1, -2, 3, -4);
  Tuple negated = -a;
  REQUIRE( negated.getX() == Approx(-1) );
  REQUIRE( negated.getY() == Approx(2) );
  REQUIRE( negated.getZ() == Approx(-3) );
  REQUIRE( negated.getW() == Approx(4) );
}

TEST_CASE ("Multiplying tuple by a scalar", "[tuple]") {
  Tuple tup = Tuple(1, -2, 3, -4);
  Tuple res = tup * 3.5;
  REQUIRE( res.getX() == Approx(3.5) );
  REQUIRE( res.getY() == Approx(-7) );
  REQUIRE( res.getZ() == Approx(10.5) );
  REQUIRE( res.getW() == Approx(-14) );
}

TEST_CASE ("Multiplying tuple by a fraction", "[tuple]") {
  Tuple tup = Tuple(1, -2, 3, -4);
  Tuple res = tup * 0.5;
  REQUIRE( res.getX() == Approx(0.5) );
  REQUIRE( res.getY() == Approx(-1) );
  REQUIRE( res.getZ() == Approx(1.5) );
  REQUIRE( res.getW() == Approx(-2) );
}

TEST_CASE ("Dividing a tuple by a scalar", "[tuple]") {
  Tuple tup = Tuple(1, -2, 3, -4);
  Tuple res = tup / 2;
  REQUIRE( res.getX() == Approx(0.5) );
  REQUIRE( res.getY() == Approx(-1) );
  REQUIRE( res.getZ() == Approx(1.5) );
  REQUIRE( res.getW() == Approx(-2) );
}

TEST_CASE ("Compute the magnitude of tuples", "[tuple]") {
  Tuple v1 = Tuple::create_vector(1, 0, 0);
  REQUIRE( v1.getMagnitude() == Approx(1) );

  Tuple v2 = Tuple::create_vector(0, 0, 1);
  REQUIRE( v2.getMagnitude() == Approx(1) );

  Tuple v3 = Tuple::create_vector(1, 2, 3);
  REQUIRE( v3.getMagnitude() == Approx(3.74165738) );

  Tuple v4 = Tuple::create_vector(-1, -2, -3);
  REQUIRE( v4.getMagnitude() == Approx(3.74165738) );
}

TEST_CASE ("Normalizing tuples", "[tuple]") {
  Tuple v1 = Tuple::create_vector(4, 0, 0);
  Tuple v1n = v1.getNormalized();
  REQUIRE( v1n.getX() == Approx(1) );
  REQUIRE( v1n.getY() == Approx(0) );
  REQUIRE( v1n.getZ() == Approx(0) );

  Tuple v2 = Tuple::create_vector(1, 2, 3);
  Tuple v2n = v2.getNormalized();
  REQUIRE( v2n.getX() == Approx(0.26726) );
  REQUIRE( v2n.getY() == Approx(0.53452) );
  REQUIRE( v2n.getZ() == Approx(0.80178) );

  REQUIRE ( v2n.getMagnitude() == Approx(1) );
}

TEST_CASE ("Dot product of two vectors", "[tuple]") {
  Tuple a = Tuple::create_vector(1, 2, 3);
  Tuple b = Tuple::create_vector(2, 3, 4);
  auto dot = dotProduct(a, b);
  REQUIRE ( dot == Approx(20) );
}

TEST_CASE ("Cross product of two vectors", "[tuple]") {
  Tuple a = Tuple::create_vector(1, 2, 3);
  Tuple b = Tuple::create_vector(2, 3, 4);
  auto crossab = crossProduct(a, b);
  REQUIRE( crossab.getX() == Approx(-1) );
  REQUIRE( crossab.getY() == Approx(2) );
  REQUIRE( crossab.getZ() == Approx(-1) );

  auto crossba = crossProduct(b, a);
  REQUIRE( crossba.getX() == Approx(1) );
  REQUIRE( crossba.getY() == Approx(-2) );
  REQUIRE( crossba.getZ() == Approx(1) );
}
