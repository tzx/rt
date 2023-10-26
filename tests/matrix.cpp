#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

#include "../src/matrix.hpp"
#include "../src/tuple.hpp"

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

TEST_CASE ("Multiple matrix by tuple", "[matrices]") {
  std::vector<float> values = { 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
  Matrix m = Matrix(4, 4, values);
  Tuple b = Tuple(1, 2, 3, 1);

  Tuple prod = m * b;
  REQUIRE( prod.getX() == Approx(18) );
  REQUIRE( prod.getY() == Approx(24) );
  REQUIRE( prod.getZ() == Approx(33) );
  REQUIRE( prod.getW() == Approx(1) );
}

TEST_CASE ("Multiplying matrix by identity matrix", "[matrices]") {
  std::vector<float> values = { 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
  Matrix m = Matrix(4, 4, values);
  Matrix i = Matrix::identity_matrix(4);
  Matrix prod = m * i;
  REQUIRE( prod == m );

  Tuple tup = Tuple(1, 2, 3, 4);
  Tuple tup_prod = i * tup;

  REQUIRE( tup.getX() == Approx(tup_prod.getX()) );
  REQUIRE( tup.getY() == Approx(tup_prod.getY()) );
  REQUIRE( tup.getZ() == Approx(tup_prod.getZ()) );
  REQUIRE( tup.getW() == Approx(tup_prod.getW()) );
}

TEST_CASE ("Transposing a matrix", "[matrices]") {
  std::vector<float> values = { 0, 9, 3, 0,
                                9, 8, 0, 8,
                                1, 8, 5, 3,
                                0, 0, 5, 8};
  Matrix m = Matrix(4, 4, values);

  std::vector<float> transposed_values = {0, 9, 1, 0,
                                          9, 8, 8, 0,
                                          3, 0, 5, 5,
                                          0, 8, 3, 8};
  Matrix tp = Matrix(4, 4, transposed_values);

  Matrix t = m.transpose();
  REQUIRE( t == tp );
}

TEST_CASE ("Transposing the identity matrix", "[matrices]") {
  Matrix i = Matrix::identity_matrix(4);

  REQUIRE( i == i.transpose() );
}

TEST_CASE ("Calculating the determinant of a 2x2 matrix", "[matrices]") {
  std::vector<float> values = { 1, 5, -3, 2 };
  Matrix m = Matrix(2, 2, values);

  REQUIRE( m.determinant() == Approx(17) );
}

TEST_CASE ("A submatrix of a 3x3 matrix is 2x2 matrix", "[matrices]") {
  std::vector<float> values = {1, 5, 0, -3, 2, 7, 0, 6, -3};
  Matrix m = Matrix(3, 3, values);

  std::vector<float> expected_values = {-3, 2, 0, 6};
  Matrix expected = Matrix(2, 2, expected_values);

  REQUIRE (m.submatrix(0, 2) == expected);
}

TEST_CASE ("A submatrix of a 4x4 matrix is 3x3 matrix", "[matrices]") {
  std::vector<float> values = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
  Matrix m = Matrix(4, 4, values);

  std::vector<float> expected_values = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
  Matrix expected = Matrix(3, 3, expected_values);

  REQUIRE (m.submatrix(2, 1) == expected);
}
