#include "matrix.hpp"
#include <cmath>
#include <vector>

Matrix Matrix::translation(float x, float y, float z) {
  std::vector<float> values = {1, 0, 0, x,
                               0, 1, 0, y,
                               0, 0, 1, z,
                               0, 0, 0, 1};
  return Matrix(4, 4, values);
}

Matrix Matrix::scaling(float x, float y, float z) {
  std::vector<float> values = {x, 0, 0, 0,
                               0, y, 0, 0,
                               0, 0, z, 0,
                               0, 0, 0, 1};
  return Matrix(4, 4, values);
}

Matrix Matrix::rotation_x(float r) {
  std::vector<float> values = {1, 0, 0, 0,
                               0, std::cos(r), -std::sin(r), 0,
                               0, std::sin(r), std::cos(r), 0,
                               0, 0, 0, 1};
  return Matrix(4, 4, values);
}

Matrix Matrix::rotation_y(float r) {
  std::vector<float> values = {std::cos(r), 0, std::sin(r), 0,
                               0, 1, 0, 0,
                               -std::sin(r), 0, std::cos(r), 0,
                               0, 0, 0, 1};
  return Matrix(4, 4, values);
}

Matrix Matrix::rotation_z(float r) {
  std::vector<float> values = {std::cos(r), -std::sin(r), 0, 0,
                               std::sin(r), std::cos(r), 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1};
  return Matrix(4, 4, values);
}
