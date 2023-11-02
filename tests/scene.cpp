#include <catch2/catch.hpp>

#include "../src/canvas/color.hpp"
#include "../src/canvas/world.hpp"
#include "../src/lights/point_light.hpp"
#include "../src/primitives/tuple.hpp"
#include "../src/sphere.hpp"

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
