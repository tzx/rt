#include <catch2/catch.hpp>
#include <cmath>

#include "../src/shapes/sphere.hpp"
#include "../src/canvas/color.hpp"
#include "../src/lights/point_light.hpp"

TEST_CASE ("The normal on a sphere at a point on the x axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(1, 0, 0), fake_hit);
  REQUIRE (n == Tuple::create_vector(1, 0, 0));
}

TEST_CASE ("The normal on a sphere at a point on the y axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(0, 1, 0), fake_hit);
  REQUIRE (n == Tuple::create_vector(0, 1, 0));
}

TEST_CASE ("The normal on a sphere at a point on the z axis", "[normal]") {
  Sphere s = Sphere();
  Tuple n = s.normal_at(Tuple::create_point(0, 0, 1), fake_hit);
  REQUIRE (n == Tuple::create_vector(0, 0, 1));
}

TEST_CASE ("The normal on a sphere at a nonaxial point", "[normal]") {
  Sphere s = Sphere();
  float root3over3 = std::sqrt(3)/3.0f;
  Tuple n = s.normal_at(Tuple::create_point(root3over3, root3over3, root3over3), fake_hit);
  REQUIRE (n == Tuple::create_vector(root3over3, root3over3, root3over3));
}

TEST_CASE ("The normal is a normalized vector", "[normal]") {
  Sphere s = Sphere();
  float root3over3 = std::sqrt(3)/3.0f;
  Tuple n = s.normal_at(Tuple::create_point(root3over3, root3over3, root3over3), fake_hit);
  REQUIRE (n == n.getNormalized());
}

TEST_CASE ("Computing the normal on a translated sphere", "[normal]") {
  Sphere s = Sphere();
  s.setTransform(Mat4::translation(0, 1, 0));
  Tuple n = s.normal_at(Tuple::create_point(0, 1.70711, -0.70711), fake_hit);
  REQUIRE (n == n.create_vector(0, 0.70711, -0.70711));
}

TEST_CASE ("Computing the normal on a transformed sphere", "[normal]") {
  Sphere s = Sphere();
  auto m = Mat4::scaling(1, 0.5, 1) * Mat4::rotation_z(M_PIf/5.0f);
  s.setTransform(m);

  float sqpi2 = std::sqrt(2)/2.0f;
  Tuple n = s.normal_at(Tuple::create_point(0, sqpi2, -sqpi2), fake_hit);
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

TEST_CASE ("A point light has a position and intensity", "[phong]") {
  Color intensity = Color(1, 1, 1);
  Tuple position = Tuple::create_point(0, 0, 0);

  PointLight light = PointLight(position, intensity);

  REQUIRE (light.position() == position);
  REQUIRE (light.intensity() == intensity);
}

TEST_CASE ("The default material", "[phong]") {
  Material m = Material();

  REQUIRE (m.color() == Color(1, 1, 1));
  REQUIRE (m.ambient() == 0.1f);
  REQUIRE (m.diffuse() == 0.9f);
  REQUIRE (m.specular() == 0.9f);
  REQUIRE (m.shininess() == 200.0f);
}

TEST_CASE ("A sphere has no material", "[phong]") {
  Sphere s = Sphere();
  Material m = *s.material();

  REQUIRE (m == Material());
}

TEST_CASE ("A sphere may be assigned a material", "[phong]") {
  Sphere s = Sphere();
  s.material()->setAmbient(1);
  Material m = Material();
  m.setAmbient(1);

  REQUIRE (*s.material() == m);
}

TEST_CASE ("Lighting with the eye between the light and the surface", "[phong]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 0, -10), Color(1, 1, 1));

  Sphere obj;
  Color result = m.lighting(&obj, light, position, eyev, normalv);
  REQUIRE (result == Color(1.9, 1.9, 1.9));
}

TEST_CASE ("Lighting with the eye between the light and the surface, eye offset 45deg", "[phong]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  float sq2_2 = std::sqrt(2)/2.0f;

  Tuple eyev = Tuple::create_vector(0, sq2_2, -sq2_2);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 0, -10), Color(1, 1, 1));

  Sphere obj;
  Color result = m.lighting(&obj, light, position, eyev, normalv);
  REQUIRE (result == Color(1.0, 1.0, 1.0));
}

TEST_CASE ("Lighting with eye opposite surface, light offset 45deg", "[phong]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 10, -10), Color(1, 1, 1));

  Sphere obj;
  Color result = m.lighting(&obj, light, position, eyev, normalv);
  REQUIRE (result == Color(0.7364, 0.7364, 0.7364));
}

TEST_CASE ("Lighting with eye in the path of the reflection vector", "[phong]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  float sq2_2 = std::sqrt(2)/2.0f;

  Tuple eyev = Tuple::create_vector(0, -sq2_2, -sq2_2);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 10, -10), Color(1, 1, 1));

  Sphere obj;
  Color result = m.lighting(&obj, light, position, eyev, normalv);

  REQUIRE (result == Color(1.63639, 1.63639, 1.63639));
}

TEST_CASE ("Lighting with light behind the surface", "[phong]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight light = PointLight(Tuple::create_point(0, 0, 10), Color(1, 1, 1));

  Sphere obj;
  Color result = m.lighting(&obj, light, position, eyev, normalv);
  REQUIRE (result == Color(0.1, 0.1, 0.1));
}

TEST_CASE ("Lighting with the surface in the shadow", "[shadow]") {
  Material m = Material();
  Tuple position = Tuple::create_point(0, 0, 0);

  Tuple eyev = Tuple::create_vector(0, 0, -1);
  Tuple normalv = Tuple::create_vector(0, 0, -1);
  PointLight point_light(Tuple::create_point(0, 0, -10), Color(1, 1, 1));

  bool in_shadow = true;
  Sphere obj;
  Color result = m.lighting(&obj,point_light, position, eyev, normalv, in_shadow);

  REQUIRE (result == Color(0.1, 0.1, 0.1) );
}
