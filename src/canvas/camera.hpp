#pragma once

#include "../primitives/matrix.hpp"
#include "../ray.hpp"
#include "../canvas/canvas.hpp"
#include "world.hpp"

class Camera {
  public:
    Camera(int hsize, int vsize, float fov);

    int hsize() const;
    int vsize() const;
    float fov() const;
    Matrix transform() const;
    void setTransform(Matrix m);
    float half_width() const;
    float half_height() const;

    float pixel_size() const;
    Ray ray_for_pixel(int px, int py) const;
    Canvas render(World w) const;

  private:
    int hsize_;
    int vsize_;
    float fov_;
    Matrix transform_;

    float half_width_;
    float half_height_;
    float pixel_size_;
};
