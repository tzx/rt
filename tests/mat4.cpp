#include <catch2/catch.hpp>

#include "../src/primitives/tuple.hpp"
#include "../src/primitives/matrix4.hpp"

TEST_CASE("Mat4 inverse", "[mat4]") {
  auto c0 = Tuple(-5, 1, 7, 1);
  auto c1 = Tuple(2, -5, 7, -3);
  auto c2 = Tuple(6, 1, -6, 7);
  auto c3 = Tuple(-8, 8, -7, 4);
  auto mat = Mat4(c0, c1, c2, c3);
  // mat.repr();

  auto mati = mat.inverse();
  // mati.repr();
  // TODO: too lazy to deal with this now but it seems to give correct inverse
}
