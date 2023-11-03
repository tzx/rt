#include <catch2/catch.hpp>
#include <cmath>

#include "../src/primitives/matrix.hpp"
#include "../src/shapes/test_shape.hpp"

TEST_CASE("The default transformation", "[shape]") {
  TestShape s = TestShape();
  REQUIRE(s.transform() == Matrix::identity_matrix(4));
}

TEST_CASE("Assigning a transformation", "[shape]") {
  TestShape s = TestShape();
  s.setTransform(Matrix::translation(2, 3, 4));
  REQUIRE(s.transform() == Matrix::translation(2, 3, 4));
}

TEST_CASE("The default material shape", "[shape]") {
  TestShape s = TestShape();
  auto m = s.material();

  REQUIRE(*m == Material());
}

TEST_CASE("Assigning a material shape", "[shape]") {
  TestShape s = TestShape();
  s.material()->setAmbient(1);

  Material m = Material();
  m.setAmbient(1);

  REQUIRE(*s.material() == m);
}

TEST_CASE("Intersecting a scaled shape with a ray", "[shape]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  auto s = std::make_shared<TestShape>();
  s->setTransform(Matrix::scaling(2, 2, 2));
  auto xs = intersect(s, r);

  REQUIRE(s->saved_ray.value().origin() == Tuple::create_point(0, 0, -2.5));
  REQUIRE(s->saved_ray.value().direction() == Tuple::create_vector(0, 0, 0.5));
}

TEST_CASE("Intersecting a translated shape with a ray", "[shape]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  auto s = std::make_shared<TestShape>();
  s->setTransform(Matrix::translation(5, 0, 0));
  auto xs = intersect(s, r);

  REQUIRE(s->saved_ray.value().origin() == Tuple::create_point(-5, 0, -5));
  REQUIRE(s->saved_ray.value().direction() == Tuple::create_vector(0, 0, 1));
}

TEST_CASE ("Computing the normal on a translated test shape", "[shape]") {
  auto s = TestShape();
  s.setTransform(Matrix::translation(0, 1, 0));
  auto n = s.normal_at(Tuple::create_point(0, 1.70711, -0.70711));

  REQUIRE (n == Tuple::create_vector(0, 0.70711, -0.70711));
}

TEST_CASE ("Computing the normal on a transformed test shape", "[shape]") {
  auto s = TestShape();
  s.setTransform(Matrix::scaling(1, 0.5, 1) * Matrix::rotation_z(M_PIf/5));
  float sq2_2 = std::sqrt(2.0f)/2;
  auto n = s.normal_at(Tuple::create_point(0, sq2_2, -sq2_2));

  REQUIRE (n == Tuple::create_vector(0, 0.97014, -0.24254));
}
