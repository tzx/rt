#include "camera.hpp"
#include "canvas.hpp"
#include <cmath>
#include <iostream>

Camera::Camera(int hsize, int vsize, float fov)
    : transform_(Matrix::identity_matrix(4)),
      transform_inverse_(Matrix::identity_matrix(4)) {
  this->hsize_ = hsize;
  this->vsize_ = vsize;
  this->fov_ = fov;

  float half_view = std::tan(this->fov() / 2.0f);
  float aspect = (float)this->hsize() / this->vsize();

  if (aspect >= 1) {
    this->half_width_ = half_view;
    this->half_height_ = half_view / aspect;
  } else {
    this->half_width_ = half_view * aspect;
    this->half_height_ = half_view;
  }

  this->pixel_size_ = (this->half_width_ * 2) / this->hsize_;
}

int Camera::hsize() const { return this->hsize_; }

int Camera::vsize() const { return this->vsize_; }

float Camera::fov() const { return this->fov_; }

Matrix Camera::transform() const { return this->transform_; }

Matrix Camera::transform_inverse() const { return this->transform_inverse_; }

float Camera::half_width() const { return this->half_width_; }

float Camera::half_height() const { return this->half_height_; }

float Camera::pixel_size() const { return this->pixel_size_; }

void Camera::setTransform(Matrix m) { 
  this->transform_ = m; 
  this->transform_inverse_ = m.inverse();
}

Ray Camera::ray_for_pixel(int px, int py) const {
  float x_offset = (px + 0.5) * this->pixel_size();
  float y_offset = (py + 0.5) * this->pixel_size();

  float world_x = this->half_width() - x_offset;
  float world_y = this->half_height() - y_offset;

  Tuple pixel =
      this->transform_inverse() * Tuple::create_point(world_x, world_y, -1);
  Tuple origin = this->transform_inverse() * Tuple::create_point(0, 0, 0);
  Tuple direction = (pixel - origin).getNormalized();

  return Ray(origin, direction);
}

Canvas Camera::render(World w) const {
  Canvas image = Canvas(this->hsize(), this->vsize());

  for (auto y = 0; y < this->vsize(); ++y) {
    for (auto x = 0; x < this->hsize(); ++x) {
      // std::cerr << "Y: " <<  y << " --- X: " << x << std::endl;
      Ray ray = this->ray_for_pixel(x, y);
      Color color = w.color_at(ray);
      image.write_pixel(x, y, color);
    }
  }

  return image;
}
