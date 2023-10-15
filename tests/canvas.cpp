#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

TEST_CASE ("Constructing the PPM header", "[canvas]" ) {
  Canvas c = Canvas(5, 3);
  auto ppm = std::stringstream(c.ppm());

  std::vector<std::string> expected = { "P3", "5 3", "255" };
  std::string to_check;

  for (auto i = 0; i < 3; ++i) {
    std::getline(ppm, to_check, '\n');
    REQUIRE( to_check == expected[i] );
  }
}

TEST_CASE ("Constructing the PPM pixel data", "[canvas]" ) {
  Canvas c = Canvas(5, 3);
  Color c1 = Color(1.5, 0, 0);
  Color c2 = Color(0, 0.5, 0);
  Color c3 = Color(-0.5, 0, 1);
  c.write_pixel(0, 0, c1);
  c.write_pixel(2, 1, c2);
  c.write_pixel(4, 2, c3);

  auto ppm = std::stringstream(c.ppm());

  std::vector<std::string> expected = {
    "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
    "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255",
  };

  std::string to_check;
  for (auto i = 0; i < 6; ++i) {
    std::getline(ppm, to_check, '\n');
    if (i < 3) {
      continue;
    }
    REQUIRE( to_check == expected[i-3] );
  }
}

TEST_CASE ( "Splitting long lines in PPM files", "[canvas]" ) {
  Canvas can = Canvas(10, 2);
  Color color = Color(1, 0.8, 0.6);
  for (auto r = 0;  r < can.height(); ++r) {
    for (auto c = 0; c < can.width(); ++c) {
      can.write_pixel(c, r, color);
    }
  }

  auto ppm = std::stringstream(can.ppm());
  std::vector<std::string> expected = {
    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
    "153 255 204 153 255 204 153 255 204 153 255 204 153",
    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
    "153 255 204 153 255 204 153 255 204 153 255 204 153"
  };

  std::string to_check;
  for (auto i = 0; i < 7; ++i) {
    std::getline(ppm, to_check, '\n');
    if (i < 3) {
      continue;
    }
    REQUIRE ( to_check == expected[i-3] );
  }
}

TEST_CASE ("PPM files are terminated by a newline character", "[canvas]") {
  Canvas c = Canvas(5, 3);
  auto ppm = c.ppm();
  REQUIRE ( ppm.back() == '\n' );
}
