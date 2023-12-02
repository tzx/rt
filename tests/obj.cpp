#include <catch2/catch.hpp>
#include <iostream>
#include <memory>

#include "../src/primitives/tuple.hpp"
#include "../src/obj/obj_parser.hpp"
#include "../src/shapes/group.hpp"
#include "../src/shapes/smooth_triangle.hpp"

TEST_CASE("Ignoring unrecognized lines", "[obj]") {
  auto gibberish = "./tests/obj/gibberish.obj";
  auto parser = ObjParser(gibberish);

  REQUIRE (parser.lines_ignored() == 5);
}

TEST_CASE("Vertex records", "[obj]") {
  auto gibberish = "./tests/obj/file.obj";
  auto parser = ObjParser(gibberish);

  REQUIRE (parser.lines_ignored() == 0);
  REQUIRE (*parser.vertices().at(1) == Tuple::create_point(-1, 1, 0));
  REQUIRE (*parser.vertices().at(2) == Tuple::create_point(-1, 0.5, 0));
  REQUIRE (*parser.vertices().at(3) == Tuple::create_point(1, 0, 0));
  REQUIRE (*parser.vertices().at(4) == Tuple::create_point(1, 1, 0));
}

TEST_CASE("Parsing triangle faces", "[obj]") {
  auto gibberish = "./tests/obj/triangle.obj";
  auto parser = ObjParser(gibberish);

  auto g = parser.default_group();
  auto t1 = g.at(0);
  auto t2 = g.at(1);

  REQUIRE (t1->p1() == *parser.vertices().at(1));
  REQUIRE (t1->p2() == *parser.vertices().at(2));
  REQUIRE (t1->p3() == *parser.vertices().at(3));

  REQUIRE (t2->p1() == *parser.vertices().at(1));
  REQUIRE (t2->p2() == *parser.vertices().at(3));
  REQUIRE (t2->p3() == *parser.vertices().at(4));
}

TEST_CASE("Triangulating polygons", "[obj]") {
  auto file = "./tests/obj/polygon.obj";
  auto parser = ObjParser(file);

  auto g = parser.default_group();

  auto t1 = g.at(0);
  auto t2 = g.at(1);
  auto t3 = g.at(2);

  REQUIRE (t1->p1() == *parser.vertices().at(1));
  REQUIRE (t1->p2() == *parser.vertices().at(2));
  REQUIRE (t1->p3() == *parser.vertices().at(3));

  REQUIRE (t2->p1() == *parser.vertices().at(1));
  REQUIRE (t2->p2() == *parser.vertices().at(3));
  REQUIRE (t2->p3() == *parser.vertices().at(4));

  REQUIRE (t3->p1() == *parser.vertices().at(1));
  REQUIRE (t3->p2() == *parser.vertices().at(4));
  REQUIRE (t3->p3() == *parser.vertices().at(5));
}

TEST_CASE("Triangles in groups", "[obj]") {
  auto file = "./tests/obj/triangles.obj";
  auto parser = ObjParser(file);

  auto g1 = parser.group("FirstGroup");
  auto g2 = parser.group("SecondGroup");

  auto t1 = g1.at(0);
  auto t2 = g2.at(0);

  REQUIRE (t1->p1() == *parser.vertices().at(1));
  REQUIRE (t1->p2() == *parser.vertices().at(2));
  REQUIRE (t1->p3() == *parser.vertices().at(3));

  REQUIRE (t2->p1() == *parser.vertices().at(1));
  REQUIRE (t2->p2() == *parser.vertices().at(3));
  REQUIRE (t2->p3() == *parser.vertices().at(4));
}

TEST_CASE("Converting an OBJ file to a group", "[obj]") {
  auto file = "./tests/obj/triangles.obj";
  auto parser = ObjParser(file);
  auto g = parser.obj_to_group();
  REQUIRE(g->shapes().size() == 2);
}

TEST_CASE("Vertex normal records", "[obj]") {
  auto file = "./tests/obj/vertex_normal.obj";
  auto parser = ObjParser(file);

  REQUIRE( parser.normals().at(1) == Tuple::create_vector(0, 0, 1));
  REQUIRE( parser.normals().at(2) == Tuple::create_vector(0.707, 0, -0.707));
  REQUIRE( parser.normals().at(3) == Tuple::create_vector(1, 2, 3));
}

TEST_CASE("Faces with normals", "[obj]") {
  auto file = "./tests/obj/faces_with_normals.obj";
  auto parser = ObjParser(file);

  auto g = parser.default_group();
  auto t1 = std::dynamic_pointer_cast<SmoothTriangle>(g.at(0));
  auto t2 = std::dynamic_pointer_cast<SmoothTriangle>(g.at(1));

  REQUIRE (*t1 == *t2);
}
