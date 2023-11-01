#include <catch2/catch.hpp>
#include <cmath>

#include "../src/sphere.hpp"

TEST_CASE ("The normal on a sphere at a point on the x axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(1, 0, 0));
  REQUIRE (n == Tuple::create_vector(1, 0, 0));
}

TEST_CASE ("The normal on a sphere at a point on the y axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(0, 1, 0));
  REQUIRE (n == Tuple::create_vector(0, 1, 0));
}

TEST_CASE ("The normal on a sphere at a point on the z axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(0, 0, 1));
  REQUIRE (n == Tuple::create_vector(0, 0, 1));
}

TEST_CASE ("The normal on a sphere at a nonaxial point", "[normal]") {
  Sphere s = Sphere();
  float root3over3 = std::sqrt(3)/3.0f;
  Tuple n = s.normal_at(Tuple::create_point(root3over3, root3over3, root3over3));
  REQUIRE (n == Tuple::create_vector(root3over3, root3over3, root3over3));
}

TEST_CASE ("The normal is a normalized vector", "[normal]") {
  Sphere s = Sphere();
  float root3over3 = std::sqrt(3)/3.0f;
  Tuple n = s.normal_at(Tuple::create_point(root3over3, root3over3, root3over3));
  REQUIRE (n == n.getNormalized());
}

TEST_CASE ("Computing the normal on a translated sphere", "[normal]") {
  Sphere s = Sphere();
  s.setTransform(Matrix::translation(0, 1, 0));
  Tuple n = s.normal_at(Tuple::create_point(0, 1.70711, -0.70711));
  REQUIRE (n == n.create_vector(0, 0.70711, -0.70711));
}

TEST_CASE ("Computing the normal on a transformed sphere", "[normal]") {
  Sphere s = Sphere();
  Matrix m = Matrix::scaling(1, 0.5, 1) * Matrix::rotation_z(M_PIf/5.0f);
  s.setTransform(m);

  float sqpi2 = std::sqrt(2)/2.0f;
  Tuple n = s.normal_at(Tuple::create_point(0, sqpi2, -sqpi2));
  REQUIRE (n == Tuple::create_vector(0, 0.97014, -0.24254));
}

TEST_CASE ("Reflecting a vector approaching a 45 degree angle", "[reflect]") {
  Tuple v = Tuple::create_vector(1, -1, 0);
  Tuple n = Tuple::create_vector(0, 1, 0);
  Tuple r = reflect(v, n);
  REQUIRE (r == Tuple::create_vector(1, 1, 0));
}

TEST_CASE ("Reflecting a vector off a slanted surface", "[reflect]") {
  float sq2_2 = std::sqrt(2)/2.0f;
  Tuple v = Tuple::create_vector(0, -1, 0);
  Tuple n = Tuple::create_vector(sq2_2, sq2_2, 0);
  Tuple r = reflect(v, n);
  REQUIRE (r == Tuple::create_vector(1, 0, 0));
}
