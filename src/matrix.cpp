#include "matrix.hpp"
#include "approx.hpp"

Matrix::Matrix(int height, int width, std::vector<float> values) {
  w_ = width;
  h_ = height;
  values_ = std::vector<float>(w_ * h_);

  for (auto i = 0; i < values.size(); ++i) {
    values_[i] = values[i];
  }
}

int Matrix::height() const {
  return h_;
}

int Matrix::width() const {
  return w_;
}

inline int Matrix::idx(int row, int col) const {
  return row * w_ + col;
}

float& Matrix::operator()(int row, int col) {
  int index = idx(row, col);
  return values_[index];
}

float Matrix::at(int row, int col) const {
  int index = idx(row, col);
  return values_[index];
}

Matrix operator*(const Matrix &self, const Matrix &other) {
  // TODO: we don't check dimensions of self.width() == other.height()
  Matrix res = Matrix(self.height(), other.width(), {});
  for (auto r = 0; r < self.height(); ++r) {
    for (auto c = 0; c < other.width(); ++c) {
      float val = 0;
      for (auto k = 0; k < self.width(); ++k) {
        val += self.at(r, k) * other.at(k, c);
      }
      res(r, c) = val;
    }
  }
  return res;
}

bool operator==(const Matrix &self, const Matrix &other) {
  if (self.width() != other.width() || self.height() != other.height()) {
    return false;
  }
  for (auto r = 0; r < self.height(); ++r) {
    for (auto c = 0; c < self.width(); ++c) {
      if (!approx_eq(self.at(r, c), other.at(r, c))) {
        return false;
      }
    }
  }
  return true;
}
