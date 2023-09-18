#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

int add(int a, int b) {
  return a + b;
}

TEST_CASE( "Add two numbers", "[add]" ) {
  REQUIRE( add(1, 2) == 3 );
}
