#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

#include "../src/matrix.hpp"

TEST_CASE ("Constructing and inspecting a 4x4", "[matrices]") {
  std::vector<float> values = {1, 2, 3, 4,
                               5.5, 6.5, 7.5, 8.5,
                               9, 10, 11, 12,
                               13.5, 14.5, 15.5, 16.5};

  Matrix m = Matrix(4, 4, values);
  REQUIRE( m(0, 0) == Approx(1) );
  REQUIRE( m(0, 3) == Approx(4) );
  REQUIRE( m(1, 0) == Approx(5.5) );
  REQUIRE( m(1, 2) == Approx(7.5) );
  REQUIRE( m(2, 2) == Approx(11) );
  REQUIRE( m(3, 0) == Approx(13.5) );
  REQUIRE( m(3, 2) == Approx(15.5) );
}

TEST_CASE ("A 2x2 matrix ought to be representable", "[matrices]") {
  std::vector<float> values = {-3, 5,
                               1, -2};

  Matrix m = Matrix(2, 2, values);
  REQUIRE( m(0, 0) == Approx(-3) );
  REQUIRE( m(0, 1) == Approx(5) );
  REQUIRE( m(1, 0) == Approx(1) );
  REQUIRE( m(1, 1) == Approx(-2) );
}

TEST_CASE ("A 3x3 matrix ought to be representable", "[matrices]") {
  std::vector<float> values = {-3, 5, 0,
                               1, -2, -7,
                               0, 1, 1};

  Matrix m = Matrix(3, 3, values);
  REQUIRE( m(0, 0) == Approx(-3) );
  REQUIRE( m(1, 1) == Approx(-2) );
  REQUIRE( m(2, 2) == Approx(1) );
}

TEST_CASE ("Matrix equality with identical matrices", "[matrices]") {
  std::vector<float> a_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  Matrix m_a = Matrix(4, 4, a_values);
  std::vector<float> b_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  Matrix m_b = Matrix(4, 4, b_values);

  REQUIRE( m_a == m_b );
}

TEST_CASE ("Matrix equality with different matrices", "[matrices]") {
  std::vector<float> a_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  Matrix m_a = Matrix(4, 4, a_values);
  std::vector<float> b_values = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  Matrix m_b = Matrix(4, 4, b_values);

  REQUIRE_FALSE( m_a == m_b );
}

TEST_CASE ("Multiplying two matrices", "[matrices]") {
  std::vector<float> a_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  Matrix m_a = Matrix(4, 4, a_values);
  std::vector<float> b_values = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
  Matrix m_b = Matrix(4, 4, b_values);

  std::vector<float> atimesb_values = {20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
  Matrix m_atimesb = Matrix(4, 4, atimesb_values);

  Matrix product = m_a * m_b;

  REQUIRE( product == m_atimesb );
}
