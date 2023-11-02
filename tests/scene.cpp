#include <catch2/catch.hpp>

#include "../src/canvas/color.hpp"
#include "../src/canvas/world.hpp"
#include "../src/lights/point_light.hpp"
#include "../src/primitives/tuple.hpp"
#include "../src/sphere.hpp"
#include "../src/intersection.hpp"

TEST_CASE ("Creating a world", "[world]") {
  World w = World();

  REQUIRE ( w.objects().empty() );
  REQUIRE_FALSE ( w.light().has_value() );
}

TEST_CASE ("The default world", "[world]") {
  PointLight light = PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1));

  Sphere s1 = Sphere();
  Material m1 = Material();
  m1.setColor(Color(0.8, 1.0, 0.6));
  m1.setDiffuse(0.7);
  m1.setSpecular(0.2);
  s1.setMaterial(m1);

  Sphere s2 = Sphere();
  Matrix t2 = Matrix::scaling(0.5, 0.5, 0.5);
  s2.setTransform(t2);

  World w = World::default_world();

  REQUIRE (*w.light().value() == light);
  REQUIRE (w.contains(s1));
  REQUIRE (w.contains(s2));
}

TEST_CASE ("Intersect a world with a ray", "[world]") {
  World w = World::default_world();
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));

  std::vector<Intersection> xs = w.intersect_world(r);
  
  REQUIRE (xs.size() == 4);
  REQUIRE(xs[0].t() == 4);
  REQUIRE(xs[1].t() == 4.5);
  REQUIRE(xs[2].t() == 5.5);
  REQUIRE(xs[3].t() == 6);
}

TEST_CASE ("Precomputing the state of an intersection", "[computations]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  Sphere shape = Sphere();
  Intersection i = Intersection(4, shape);

  Computations comps = Computations(i, r);

  REQUIRE (comps.t() == i.t());
  REQUIRE(comps.object() == i.object());
  REQUIRE(comps.point() == Tuple::create_point(0, 0, -1));
  REQUIRE(comps.eyev() == Tuple::create_vector(0, 0, -1));
  REQUIRE(comps.normalv() == Tuple::create_vector(0, 0, -1));
}

TEST_CASE ("The hit, when an intersection occurs on the outside", "[computations]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  Sphere shape = Sphere();
  Intersection i = Intersection(4, shape);

  Computations comps = Computations(i, r);

  REQUIRE_FALSE (comps.inside());
}

TEST_CASE ("The hit, when an intersection occurs on the inside", "[computations]") {
  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));
  Sphere shape = Sphere();
  Intersection i = Intersection(1, shape);

  Computations comps = Computations(i, r);

  REQUIRE(comps.point() == Tuple::create_point(0, 0, 1));
  REQUIRE(comps.eyev() == Tuple::create_vector(0, 0, -1));
  REQUIRE(comps.inside());
  REQUIRE(comps.normalv() == Tuple::create_vector(0, 0, -1));
}

TEST_CASE ("Shading an intersection", "[shading]") {
  World w = World::default_world();
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));

  Sphere shape = *w.objects()[0];
  Intersection i = Intersection(4, shape);

  Computations comps = Computations(i, r);

  Color c = w.shade_hit(comps);

  REQUIRE (c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE ("Shading an intersection from the inside", "[shading]") {
  World w = World::default_world();
  w.setLight(PointLight(Tuple::create_point(0, 0.25, 0), Color(1, 1, 1)));

  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));
  Sphere shape = *w.objects()[1];

  Intersection i = Intersection(0.5, shape);

  Computations comps = Computations(i, r);

  Color c = w.shade_hit(comps);

  REQUIRE (c == Color(0.90498, 0.90498, 0.90498));
}

TEST_CASE ("The color when a ray misses", "[color]") {
  World w = World::default_world();
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 1, 0));
  Color c = w.color_at(r);

  REQUIRE( c == Color(0, 0, 0) );
}

TEST_CASE ("The color when a ray hits", "[color]") {
  World w = World::default_world();
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  Color c = w.color_at(r);

  REQUIRE( c == Color(0.38066, 0.47583, 0.2855) );
}

TEST_CASE ("The color with an intersection behind the ray", "[color]") {
  World w = World::default_world();
  // TODO: You, maybe make a shared pointer for material because i am copying right now
  auto outer = w.objects().front();
  auto outer_mat = outer->material();
  outer_mat.setAmbient(1);
  outer->setMaterial(outer_mat);

  auto inner = w.objects().at(1);
  auto inner_mat = inner->material();
  inner_mat.setAmbient(1);
  inner->setMaterial(inner_mat);

  Ray r = Ray(Tuple::create_point(0, 0, 0.75), Tuple::create_vector(0, 0, -1));
  Color c = w.color_at(r);

  REQUIRE( c == inner->material().color() );
}
