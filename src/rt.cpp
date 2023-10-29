#include <cmath>
#include <iostream>
#include <ostream>

#include "canvas/canvas.hpp"
#include "primitives/matrix.hpp"
#include "primitives/tuple.hpp"

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

constexpr int LENGTH = 20;
constexpr int LINE_INSET = 200;
constexpr int DIMENSION = 2 * LINE_INSET + 4 * LENGTH;
constexpr int INSET = DIMENSION/2;

int main () {
  Canvas c = Canvas(DIMENSION, DIMENSION);

  Matrix rotation = Matrix::rotation_z(M_PI / 6.0f);
  Tuple point = Tuple::create_point(0, LINE_INSET + LENGTH, 0);

  // We have 12 points
  for (auto hour = 0; hour < 12; ++hour) {
    c.write_pixel(point.getX() + INSET, INSET + point.getY(), Color(1, 1, 1));
    point = rotation * point;
  }

  std::cout << c.ppm();

  return 0;
}
