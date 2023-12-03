#include "matrix4.hpp"
#include <iostream>

void Mat4::repr() const {
  for (auto r = 0; r < 4; ++r) {
    for (auto c = 0; c < 4; ++c) {
      std::cout << this->at(r, c) << ", ";
    }
    std::cout << std::endl;
  }
}
