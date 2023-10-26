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

TEST_CASE ("Calculating a minor of a 3x3 matrix", "[matrices]") {
  std::vector<float> values = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  Matrix a = Matrix(3, 3, values);
  Matrix b = a.submatrix(1, 0);
  float b_det = b.determinant();

  REQUIRE ( b_det == Approx(a.minor(1, 0)) );
}

TEST_CASE ("Calculating a cofactor of a 3x3 matrix", "[matrices]") {
  std::vector<float> values = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  Matrix a = Matrix(3, 3, values);

  REQUIRE( a.minor(0, 0) == Approx(-12) );
  REQUIRE( a.cofactor(0, 0) == Approx(-12) );
  REQUIRE( a.minor(1, 0) == Approx(25) );
  REQUIRE( a.cofactor(1, 0) == Approx(-25) );
}

TEST_CASE ("Calculating the determinant of a 3x3 matrix", "[matrices]") {
  std::vector<float> values = {1, 2, 6, -5, 8, -4, 2, 6, 4};
  Matrix a = Matrix(3, 3, values);

  REQUIRE( a.cofactor(0, 0) == Approx(56) );
  REQUIRE( a.cofactor(0, 1) == Approx(12) );
  REQUIRE( a.cofactor(0, 2) == Approx(-46) );
  REQUIRE( a.determinant() == Approx(-196) );
}

TEST_CASE ("Calculating the determinant of a 4x4 matrix", "[matrices]") {
  std::vector<float> values = {-2, -8, 3, 5,
                               -3, 1, 7, 3,
                               1, 2, -9, 6,
                               -6, 7, 7, -9};
  Matrix a = Matrix(4, 4, values);

  REQUIRE( a.cofactor(0, 0) == Approx(690) );
  REQUIRE( a.cofactor(0, 1) == Approx(447) );
  REQUIRE( a.cofactor(0, 2) == Approx(210) );
  REQUIRE( a.cofactor(0, 3) == Approx(51) );
  REQUIRE( a.determinant() == Approx(-4071) );
}

TEST_CASE ("Testing an invertible matrix for invertibility", "[matrices]") {
  std::vector<float> values = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
  Matrix a = Matrix(4, 4, values);

  REQUIRE ( a.determinant() == Approx(-2120) );
  REQUIRE ( a.invertible() );
}

TEST_CASE ("Testing an noninvertible matrix for invertibility", "[matrices]") {
  std::vector<float> values = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
  Matrix a = Matrix(4, 4, values);

  REQUIRE ( a.determinant() == Approx(0) );
  REQUIRE_FALSE ( a.invertible() );
}

TEST_CASE ("Calculating the inverse of a matrix", "[matrices]") {
  std::vector<float> values = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
  Matrix a = Matrix(4, 4, values);
  Matrix b = a.inverse();

  REQUIRE ( a.determinant() == Approx(532) );
  REQUIRE ( a.cofactor(2, 3) == Approx(-160) );
  REQUIRE ( b.at(3, 2) == Approx(-160.f/532.f) );
  REQUIRE ( a.cofactor(3, 2) == Approx(105) );
  REQUIRE ( b.at(2, 3) == Approx(105.f/532.f) );

  std::vector<float> expected_b_values = { 0.21805, 0.45113, 0.24060, -0.04511,
                                    -0.80827, -1.45677, -0.44361, 0.52068,
                                    -0.07895, -0.22368, -0.05263, 0.19737,
                                    -0.52256, -0.81391, -0.30075, 0.30639
                                  };
  Matrix expected_b = Matrix(4, 4, expected_b_values);

  REQUIRE (b == expected_b);
}

TEST_CASE ("Calculating the inverse of other matrices", "[matrices]") {
  std::vector<float> values_a = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
  Matrix a = Matrix(4, 4, values_a);

  std::vector<float> values_ai = { -0.15385, -0.15385, -0.28205, -0.53846,
                                   -0.07692,  0.12308,  0.02564, 0.03077,
                                    0.35897,  0.35897,  0.43590, 0.92308,
                                   -0.69231, -0.69231, -0.76923, -1.92308
                                  };

  Matrix ai = Matrix(4, 4, values_ai);
  REQUIRE ( a.inverse() == ai );


  std::vector<float> values_b = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
  Matrix b = Matrix(4, 4, values_b);

  std::vector<float> values_bi = { -0.04074, -0.07778, 0.14444, -0.22222,
                                   -0.07778,  0.03333, 0.36667, -0.33333,
                                   -0.02901, -0.14630, -0.10926, 0.12963,
                                    0.17778,  0.06667, -0.26667, 0.33333
                                  };

  Matrix bi = Matrix(4, 4, values_bi);
  REQUIRE ( b.inverse() == bi );
}

TEST_CASE ("Multiplying a matrix by its inverse", "[matrices]") {
  std::vector<float> values_a = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
  Matrix a = Matrix(4, 4, values_a);
  std::vector<float> values_b = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
  Matrix b = Matrix(4, 4, values_b);

  Matrix c = a * b;

  REQUIRE( c * b.inverse() == a );
}
