#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "color.hpp"

class Canvas {
  public:
    Canvas(int w, int h);

    int width() const;
    int height() const;
    const std::vector<std::vector<Color>>& colors() const;

    void write_pixel(int, int, Color);
    const Color& pixel_at(int, int) const;
    std::string ppm() const;

  private:
    int _width;
    int _height;
    std::vector<std::vector<Color>> _colors;
    std::string ppm_header() const;
};

int get_scaled_value(float v);
void write_color(std::stringstream &stream, float fcolor, int &col);
