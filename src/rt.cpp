#include <iostream>

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

int main () {
  struct Projectile prjtle;
  prjtle.position = Tuple::create_point(0, 1, 0);
  prjtle.velocity = Tuple::create_vector(1, 1, 0).getNormalized();

  struct Environment env;
  env.gravity = Tuple::create_vector(0, -0.1, 0);
  env.wind = Tuple::create_vector(-0.01, 0, 0);

  while (prjtle.position.getY() >= 0) {
    std::cout << "X: " << prjtle.position.getX() << ", Y: " << prjtle.position.getY() << ", Z: " << prjtle.position.getZ() << std::endl;
    prjtle = tick(env, prjtle);
  }

  return 0;
}
