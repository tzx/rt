#include <catch2/catch.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "../src/canvas/color.hpp"
#include "../src/canvas/world.hpp"
#include "../src/canvas/camera.hpp"
#include "../src/lights/point_light.hpp"
#include "../src/primitives/tuple.hpp"
#include "../src/util/approx.hpp"
#include "../src/shapes/sphere.hpp"
#include "../src/intersection.hpp"

TEST_CASE ("Creating a world", "[world]") {
  World w = World();

  REQUIRE ( w.objects().empty() );
  REQUIRE_FALSE ( w.light().has_value() );
}

TEST_CASE ("The default world", "[world]") {
  PointLight light = PointLight(Tuple::create_point(-10, 10, -10), Color(1, 1, 1));

  Sphere s1 = Sphere();
  auto m1 = s1.material();
  m1->setColor(Color(0.8, 1.0, 0.6));
  m1->setDiffuse(0.7);
  m1->setSpecular(0.2);

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
  auto shape = std::make_shared<Sphere>();
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
  auto shape = std::make_shared<Sphere>();
  Intersection i = Intersection(4, shape);

  Computations comps = Computations(i, r);

  REQUIRE_FALSE (comps.inside());
}

TEST_CASE ("The hit, when an intersection occurs on the inside", "[computations]") {
  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));
  auto shape = std::make_shared<Sphere>();
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

  auto shape = w.objects()[0];
  Intersection i = Intersection(4, shape);

  Computations comps = Computations(i, r);

  Color c = w.shade_hit(comps);

  REQUIRE (c == Color(0.380637, 0.475797, 0.285478));
}

TEST_CASE ("Shading an intersection from the inside", "[shading]") {
  World w = World::default_world();
  w.setLight(PointLight(Tuple::create_point(0, 0.25, 0), Color(1, 1, 1)));

  Ray r = Ray(Tuple::create_point(0, 0, 0), Tuple::create_vector(0, 0, 1));
  auto shape = w.objects()[1];

  Intersection i = Intersection(0.5, shape);

  Computations comps = Computations(i, r);

  Color c = w.shade_hit(comps);

  REQUIRE (c == Color(0.904662, 0.904662, 0.904662));
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

  REQUIRE (c == Color(0.380637, 0.475797, 0.285478));
}

TEST_CASE ("The color with an intersection behind the ray", "[color]") {
  World w = World::default_world();
  // TODO: You, maybe make a shared pointer for material because i am copying right now
  auto outer = w.objects().front();
  auto outer_mat = outer->material();
  outer_mat->setAmbient(1);

  auto inner = w.objects().at(1);
  auto inner_mat = inner->material();
  inner_mat->setAmbient(1);

  Ray r = Ray(Tuple::create_point(0, 0, 0.75), Tuple::create_vector(0, 0, -1));
  Color c = w.color_at(r);

  REQUIRE ( c == inner->material()->color() );
}

TEST_CASE ("The transformation matrix for the default orientation", "[transformation]") {
  Tuple from = Tuple::create_point(0, 0, 0);
  Tuple to = Tuple::create_point(0, 0, -1);
  Tuple up = Tuple::create_vector(0, 1, 0);

  Matrix t = view_transform(from, to, up);

  REQUIRE (t == Matrix::identity_matrix(4));
}

TEST_CASE ("A view transformation matrix looking in the positive z direction", "[transformation]") {
  Tuple from = Tuple::create_point(0, 0, 0);
  Tuple to = Tuple::create_point(0, 0, 1);
  Tuple up = Tuple::create_vector(0, 1, 0);

  Matrix t = view_transform(from, to, up);

  REQUIRE (t == Matrix::scaling(-1, 1, -1));
}

TEST_CASE ("The view transformation moves the world", "[transformation]") {
  Tuple from = Tuple::create_point(0, 0, 8);
  Tuple to = Tuple::create_point(0, 0, 0);
  Tuple up = Tuple::create_vector(0, 1, 0);

  Matrix t = view_transform(from, to, up);

  REQUIRE (t == Matrix::translation(0, 0, -8));
}

TEST_CASE ("An arbitary view transformation", "[transformation]") {
  Tuple from = Tuple::create_point(1, 3, 2);
  Tuple to = Tuple::create_point(4, -2, 8);
  Tuple up = Tuple::create_vector(1, 1, 0);

  Matrix t = view_transform(from, to, up);

  std::vector<float> values = { -0.50709, 0.50709, 0.67612, -2.36643,
                                 0.76772, 0.60609, 0.12122, -2.82843,
                                 -0.35857, 0.59761, -0.71714, 0.0000,
                                 0.0000, 0.0, 0.0, 1.0 };



  Matrix m = Matrix(4, 4, values);
  REQUIRE (t == m);
}

TEST_CASE ("Constructing a camera", "[camera]") {
  int hsize = 160;
  int vsize = 120;
  float fov = M_PI_2f;

  Camera c = Camera(hsize, vsize, fov);

  REQUIRE (c.hsize() == hsize);
  REQUIRE (c.vsize() == vsize);
  REQUIRE (c.fov() == fov);
  REQUIRE (c.transform() == Matrix::identity_matrix(4));
}

TEST_CASE ("The pixel size for a horizontal canvas", "[camera]") {
  Camera c = Camera(200, 125, M_PI_2f);

  REQUIRE (c.pixel_size() == 0.01f);
}

TEST_CASE ("The pixel size for a vertical canvas", "[camera]") {
  Camera c = Camera(125, 200, M_PI_2f);

  REQUIRE (c.pixel_size() == 0.01f);
}

TEST_CASE ("Constructing a ray through the center of the canvas", "[camera]") {
  Camera c = Camera(201, 101, M_PI_2f);
  Ray r = c.ray_for_pixel(100, 50);

  REQUIRE (r.origin() == Tuple::create_point(0, 0, 0));
  REQUIRE (r.direction() == Tuple::create_vector(0, 0, -1));
}

TEST_CASE ("Constructing a ray through a corner of the canvas", "[camera]") {
  Camera c = Camera(201, 101, M_PI_2f);
  Ray r = c.ray_for_pixel(0, 0);

  REQUIRE (r.origin() == Tuple::create_point(0, 0, 0));
  REQUIRE (r.direction() == Tuple::create_vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE ("Constructing a ray when the camera is transformed", "[camera]") {
  Camera c = Camera(201, 101, M_PI_2f);
  c.setTransform(Matrix::rotation_y(M_PI_4f) * Matrix::translation(0, -2, 5));

  Ray r = c.ray_for_pixel(100, 50);

  float sq2_2 = std::sqrt(2)/2.0f;

  REQUIRE ( r.origin() == Tuple::create_point(0, 2, -5) );
  REQUIRE ( r.direction() == Tuple::create_vector(sq2_2, 0, -sq2_2) );
}

TEST_CASE ("Rendering a world with a camera", "[camera]") {
  World w = World::default_world();
  Camera c = Camera(11, 11, M_PI_2f);
  Tuple from = Tuple::create_point(0, 0, -5);
  Tuple to = Tuple::create_point(0, 0, 0);
  Tuple up = Tuple::create_vector(0, 1, 0);
  c.setTransform(view_transform(from, to, up));

  Canvas image = c.render(w);

  REQUIRE (image.pixel_at(5, 5) == Color(0.380637, 0.475797, 0.285478));
}

TEST_CASE ("There is no shadow when nothing is collinear with point and light", "[shadow]") {
  World w = World::default_world();
  Tuple p = Tuple::create_point(0, 10, 0);

  REQUIRE_FALSE ( w.is_shadowed(p) );
}

TEST_CASE ("The shadow when an object is between the point and the light", "[shadow]") {
  World w = World::default_world();
  Tuple p = Tuple::create_point(10, -10, 10);

  REQUIRE ( w.is_shadowed(p) );
}

TEST_CASE ("There is no shadow when an object is behind the light", "[shadow]") {
  World w = World::default_world();
  Tuple p = Tuple::create_point(-20, 20, -20);

  REQUIRE_FALSE ( w.is_shadowed(p) );
}

TEST_CASE ("There is no shadow when an object is behind the point", "[shadow]") {
  World w = World::default_world();
  Tuple p = Tuple::create_point(-2, 2, -2);

  REQUIRE_FALSE ( w.is_shadowed(p) );
}

TEST_CASE ("shade_hit() if given an intersection in shadow", "[shadow]") {
  World w = World();
  w.setLight(PointLight(Tuple::create_point(0, 0, -10), Color(1, 1, 1)));

  auto s1 = std::make_shared<Sphere>();
  w.addObject(s1);

  auto s2 = std::make_shared<Sphere>();
  s2->setTransform(Matrix::translation(0, 0, 10));
  w.addObject(s2);

  Ray r = Ray(Tuple::create_point(0, 0, 5), Tuple::create_vector(0, 0, 1));
  Intersection i = Intersection(4, s2);

  auto comps = Computations(i, r);
  auto c = w.shade_hit(comps);

  REQUIRE (c == Color(0.1, 0.1, 0.1));
}

TEST_CASE ("The hit should offset the point", "[shadow]") {
  Ray r = Ray(Tuple::create_point(0, 0, -5), Tuple::create_vector(0, 0, 1));
  auto shape = std::make_shared<Sphere>();
  shape->setTransform(Matrix::translation(0, 0, 1));

  Intersection i = Intersection(5, shape);
  Computations comps = Computations(i, r);
  REQUIRE( comps.over_point().getZ() < -SHADOW_OFFSET/2.0f );
  REQUIRE( comps.point().getZ() > comps.over_point().getZ() );
}
