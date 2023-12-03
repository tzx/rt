#include <catch2/catch.hpp>
#include <cmath>
#include <iostream>

#include "../src/primitives/matrix4.hpp"
#include "../src/shapes/plane.hpp"
#include "../src/shapes/test_shape.hpp"

TEST_CASE("The default transformation", "[shape]") {
  TestShape s = TestShape();
  REQUIRE(s.transform() == Mat4::identity_matrix());
}

TEST_CASE("Assigning a transformation", "[shape]") {
  TestShape s = TestShape();
  s.setTransform(Mat4::translation(2, 3, 4));
  REQUIRE(s.transform() == Mat4::translation(2, 3, 4));
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
  s->setTransform(Mat4::scaling(2, 2, 2));
  auto xs = intersect(s, r);

  REQUIRE(s->saved_ray.value().origin() == Tuple::create_point(0, 0, -2.5));
  REQUIRE(s->saved_ray.value().direction() == Tuple::create_vector(0, 0, 0.5));
}

TEST_CASE("Intersecting a translated shape with a ray", "[shape]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  auto s = std::make_shared<TestShape>();
  s->setTransform(Mat4::translation(5, 0, 0));
  auto xs = intersect(s, r);

  REQUIRE(s->saved_ray.value().origin() == Tuple::create_point(-5, 0, -5));
  REQUIRE(s->saved_ray.value().direction() == Tuple::create_vector(0, 0, 1));
}

TEST_CASE("Computing the normal on a translated test shape", "[shape]") {
  auto s = TestShape();
  s.setTransform(Mat4::translation(0, 1, 0));
  auto n = s.normal_at(Tuple::create_point(0, 1.70711, -0.70711), fake_hit);

  REQUIRE(n == Tuple::create_vector(0, 0.70711, -0.70711));
}

TEST_CASE("Computing the normal on a transformed test shape", "[shape]") {
  auto s = TestShape();
  s.setTransform(Mat4::scaling(1, 0.5, 1) * Mat4::rotation_z(M_PIf / 5));
  float sq2_2 = std::sqrt(2.0f) / 2;
  auto n = s.normal_at(Tuple::create_point(0, sq2_2, -sq2_2), fake_hit);

  REQUIRE(n == Tuple::create_vector(0, 0.97014, -0.24254));
}

TEST_CASE("The normal of a plane is constant everywhere", "[shape]") {
  auto p = Plane();
  Tuple n1 = p.local_normal_at(Tuple::create_point(0, 0, 0), fake_hit);
  Tuple n2 = p.local_normal_at(Tuple::create_point(10, 0, -10), fake_hit);
  Tuple n3 = p.local_normal_at(Tuple::create_point(-5, 0, 150), fake_hit);

  REQUIRE(n1 == Tuple::create_vector(0, 1, 0));
  REQUIRE(n2 == Tuple::create_vector(0, 1, 0));
  REQUIRE(n3 == Tuple::create_vector(0, 1, 0));
}

TEST_CASE("Intersect with a ray parallel to the plane", "[shape]") {
  auto p = Plane();
  auto r = Ray(Tuple::create_point(0, 10, 0), Tuple::create_vector(0, 0, 1));

  auto xs = p.local_intersect(r);

  REQUIRE(xs.empty());
}

TEST_CASE("Intersect with a coplanar ray", "[shape]") {
  auto p = Plane();
  auto r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));

  auto xs = p.local_intersect(r);

  REQUIRE(xs.empty());
}

TEST_CASE("A ray intersecting a plane from above", "[shape]") {
  auto p = std::make_shared<Plane>();
  auto r = Ray(Tuple::create_point(0, 1, 0), Tuple::create_vector(0, -1, 0));

  auto xs = p->local_intersect(r);

  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t() == 1);
  REQUIRE(xs[0].object() == p);
}

TEST_CASE("A ray intersecting a plane from below", "[shape]") {
  auto p = std::make_shared<Plane>();
  auto r = Ray(Tuple::create_point(0, -1, 0), Tuple::create_vector(0, 1, 0));
  auto xs = p->local_intersect(r);

  REQUIRE(xs.size() == 1);
  REQUIRE(xs.at(0).t() == 1);
  REQUIRE(xs[0].object() == p);
}
