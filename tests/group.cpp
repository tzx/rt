#include <algorithm>
#include <catch2/catch.hpp>
#include <optional>

#include "../src/shapes/group.hpp"
#include "../src/shapes/test_shape.hpp"
#include "../src/shapes/sphere.hpp"

TEST_CASE("Creating a new group", "[group]") {
  auto g = Group();

  REQUIRE (g.transform() == Matrix::identity_matrix(4));
  REQUIRE (g.shapes().empty());
}

TEST_CASE("A shape has a parent attribute", "[group]") {
  auto s = TestShape();
  REQUIRE (s.parent() == std::nullopt);
}

TEST_CASE("Adding a child to a group", "[group]") {
  auto g = std::make_shared<Group>();
  auto s = std::make_shared<TestShape>();

  g->add_child(s);

  REQUIRE_FALSE (g->shapes().empty());
  REQUIRE(std::find(g->shapes().begin(), g->shapes().end(), s) != g->shapes().end());
  REQUIRE(s->parent() == g);
}

TEST_CASE("Intersecting a ray with an empty group", "[group]") {
  auto g = Group();
  auto r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));

  auto xs = g.local_intersect(r);
  REQUIRE(xs.empty());
}

TEST_CASE("Intersecting a ray with a nonempty group", "[group]") {
  auto g = std::make_shared<Group>();
  auto s1 = std::make_shared<Sphere>();
  auto s2 = std::make_shared<Sphere>();
  s2->setTransform(Matrix::translation(0, 0, -3));
  auto s3 = std::make_shared<Sphere>();
  s3->setTransform(Matrix::translation(5, 0, 0));

  g->add_child(s1);
  g->add_child(s2);
  g->add_child(s3);

  auto r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));

  auto xs = g->local_intersect(r);

  REQUIRE(xs.size() == 4);
  REQUIRE(xs.at(0).object() == s2);
  REQUIRE(xs.at(1).object() == s2);
  REQUIRE(xs.at(2).object() == s1);
  REQUIRE(xs.at(3).object() == s1);
}

TEST_CASE("Intersecting a transformed group", "[group]") {
  auto g = std::make_shared<Group>();
  g->setTransform(Matrix::scaling(2, 2, 2));
  auto s = std::make_shared<Sphere>();
  s->setTransform(Matrix::translation(5, 0, 0));

  g->add_child(s);
  auto r = Ray(Tuple::create_point(10, 0, -10), Tuple::create_vector(0, 0, 1));

  auto xs = intersect(g, r);

  REQUIRE( xs.size() == 2 );
}
