#include <iostream>

#include "tuple.hpp"

int main () {
  std::cout << "Hello World" << std::endl;

  Tuple vec = Tuple::create_vector(3, 2, 1);
  vec.repr();

  return 0;
}
