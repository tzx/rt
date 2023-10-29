#include "canvas.hpp"
#include <cmath>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int MAX_COLOR_VAL = 255;
constexpr int MAX_LINE_LEN = 70;

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

std::string Canvas::ppm() const {
  std::stringstream ppm;
  ppm << this->ppm_header();

  // UGLY AF LOL
  for (const auto &row: _colors) {
    int col = 0;
    for (const auto &cell: row) {

      write_color(ppm, cell.r(), col);
      write_color(ppm, cell.g(), col);
      write_color(ppm, cell.b(), col);
    }
    ppm << '\n';
  }

  return ppm.str();
}

void write_color(std::stringstream &stream, float fcolor, int &col) {
  int scaled = get_scaled_value(fcolor);
  auto len = std::to_string(scaled).length();

  if (col + len + std::min(col, 1) >= MAX_LINE_LEN) {
    stream << '\n';
    col = 0;
  } else if (col != 0){
    stream << " ";
    col += 1;
  }

  col += len;
  stream << scaled;
}

std::string Canvas::ppm_header() const {
  std::stringstream header;
  header << "P3" << '\n';
  header << _width << " " << _height << '\n';
  header << MAX_COLOR_VAL << '\n';
  return header.str();
}

int get_scaled_value(float v) {
  float clamped = std::max(0.0f, std::min(v, 1.0f));
  return std::lrint(clamped * MAX_COLOR_VAL);
}
