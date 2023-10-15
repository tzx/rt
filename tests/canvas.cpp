#include <catch2/catch.hpp>

#include "../src/canvas.hpp"

TEST_CASE ("Creating a canvas", "[canvas]" ) {
  Canvas c = Canvas(10, 20);
  REQUIRE( c.width() == 10 );
  REQUIRE( c.height() == 20 );

  /// https://stackoverflow.com/questions/7138588/c11-auto-what-if-it-gets-a-constant-reference
  auto& colors = c.colors();

  for (auto& rows: colors) {
    for (auto& col: rows) {
      REQUIRE( col.r() == Approx(0) );
      REQUIRE( col.g() == Approx(0) );
      REQUIRE( col.b() == Approx(0) );
    }
  }
}

TEST_CASE ("Writing pixels to a canvas", "[canvas]" ) {
  Canvas c = Canvas(10, 20);
  Color red = Color(1, 0, 0);
  c.write_pixel(2, 3, red);

  auto& pixel = c.pixel_at(2, 3);

  REQUIRE( pixel.r() == red.r() );
  REQUIRE( pixel.g() == red.g() );
  REQUIRE( pixel.b() == red.b() );
}
