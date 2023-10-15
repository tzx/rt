#include <cmath>
#include <iostream>

#include "canvas.hpp"
#include "tuple.hpp"

struct Projectile {
  Tuple position;
  Tuple velocity;
};

struct Environment {
  Tuple gravity;
  Tuple wind;
};

Projectile tick(Environment &env, Projectile &proj) {
  Projectile _new;
  _new.position = proj.position + proj.velocity;
  _new.velocity = proj.velocity + env.gravity + env.wind;
  return _new;
}

constexpr int CANVAS_HEIGHT = 550;
constexpr int CANVAS_WIDTH = 900;

int main () {
  struct Projectile prjtle;
  prjtle.position = Tuple::create_point(0, 1, 0);
  prjtle.velocity = Tuple::create_vector(1, 1.8, 0).getNormalized() * 11.25;

  struct Environment env;
  env.gravity = Tuple::create_vector(0, -0.1, 0);
  env.wind = Tuple::create_vector(-0.01, 0, 0);


  Canvas c = Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
  while (prjtle.position.getY() >= 0) {
    int x = std::lrint(prjtle.position.getX());
    int y = std::lrint(prjtle.position.getY());
    // std::cout << "X: " << prjtle.position.getX() << ", Y: " << prjtle.position.getY() << ", Z: " << prjtle.position.getZ() << std::endl;
    prjtle = tick(env, prjtle);

    c.write_pixel(x, CANVAS_HEIGHT - y, Color(1, 0, 0));
  }

  std::cout << c.ppm() << std::endl;

  return 0;
}
