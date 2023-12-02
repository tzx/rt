#include "tuple.hpp"
#include <iostream>

void Tuple::repr() const {
  std::cout << x << " " << y << " " << z << " " << w << std::endl;
}
