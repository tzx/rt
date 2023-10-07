#include "canvas.hpp"
#include <vector>

Canvas::Canvas(int width, int height) {
  _width = width;
  _height = height;

  _colors = std::vector<std::vector<Color>>(height, std::vector<Color>(width));
}

int Canvas::width() const {
  return _width;
}

int Canvas::height() const {
  return _height;
}

const std::vector<std::vector<Color>>& Canvas::colors() const {
  return _colors;
}

void Canvas::write_pixel(int width, int height, Color c) {
  // TODO: Assert they are within bounds

  auto& cell = _colors[height][width];
  cell = c;
}

const Color& Canvas::pixel_at(int width, int height) const {
  // TODO: Assert that they are within bounds

  auto& cell = _colors[height][width];
  return cell;
}
