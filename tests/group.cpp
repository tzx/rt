#include <algorithm>
#include <catch2/catch.hpp>
#include <iostream>
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

TEST_CASE("Converting a point from world to object space", "[group]") {
  auto g1 = std::make_shared<Group>();
  g1->setTransform(Matrix::rotation_y(M_PI_2f));
  auto g2 = std::make_shared<Group>();
  g2->setTransform(Matrix::scaling(2, 2, 2));

  g1->add_child(g2);

  auto s = std::make_shared<Sphere>();
  s->setTransform(Matrix::translation(5, 0, 0));

  g2->add_child(s);

  auto p = s->world_to_object(Tuple::create_point(-2, 0, -10));

  REQUIRE (p == Tuple::create_point(0, 0, -1));
}

TEST_CASE ("Converting a normal from object to world space", "[group]") {
  auto g1 = std::make_shared<Group>();
  g1->setTransform(Matrix::rotation_y(M_PI_2f));

  auto g2 = std::make_shared<Group>();
  g2->setTransform(Matrix::scaling(1, 2, 3));

  g1->add_child(g2);

  auto s = std::make_shared<Sphere>();

  s->setTransform(Matrix::translation(5, 0, 0));
  g2->add_child(s);

  auto sq3_3 = std::sqrt(3.0f)/3.0f;
  auto n = s->normal_to_world(Tuple::create_vector(sq3_3, sq3_3, sq3_3));

  REQUIRE (n == Tuple::create_vector(0.285714, 0.428571, -0.857143));
}

TEST_CASE ("Finding the normal on a child object", "[group]") {
  auto g1 = std::make_shared<Group>();
  g1->setTransform(Matrix::rotation_y(M_PI_2f));
  auto g2 = std::make_shared<Group>();
  g2->setTransform(Matrix::scaling(1, 2, 3));
  g1->add_child(g2);

  auto s = std::make_shared<Sphere>();
  s->setTransform(Matrix::translation(5, 0, 0));
  g2->add_child(s);

  auto n = s->normal_at(Tuple::create_point(1.7321, 1.1547, -5.5774), fake_hit);
  REQUIRE (n == Tuple::create_vector(0.285704, 0.428543, -0.857161));
}

TEST_CASE ("Nested group materials must be the same", "[group]") {
  auto mat = std::make_shared<Material>();
  auto parent = std::make_shared<Group>();

  auto child = std::make_shared<Group>();
  parent->set_material(mat);

  auto sph = std::make_shared<Sphere>();
  child->add_child(sph);

  parent->add_child(child);

  REQUIRE(child->material() == mat);
  REQUIRE(sph->material() == mat);
}
