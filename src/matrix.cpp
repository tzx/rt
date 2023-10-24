#include "matrix.hpp"
#include "approx.hpp"
#include "tuple.hpp"

Matrix::Matrix(int height, int width, std::vector<float> values) {
  w_ = width;
  h_ = height;
  values_ = std::vector<float>(w_ * h_);

  for (auto i = 0; i < values.size(); ++i) {
    values_[i] = values[i];
  }
}

Matrix Matrix::identity_matrix(int size) {
  auto values_ = std::vector<float>(size * size);
  for (auto r = 0; r < size; ++r) {
    for (auto c = 0; c < size; ++c) {
      if (r == c) {
        auto idx = r * size + c;
        values_[idx] = 1;
      }
    }
  }
  return Matrix(size, size, values_);
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

Matrix Matrix::transpose() const {
  Matrix res = Matrix(this->width(), this->height(), {});
  for (auto r = 0; r < this->height(); ++r) {
    for (auto c = 0; c < this->width(); ++c) {
      res(c, r) = this->at(r, c);
    }
  }
  return res;
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

Tuple operator*(const Matrix &self, const Tuple &tup) {
  // TODO: we are assuming 4x4 matrix with a 4x1 tuple

  const auto row_1 = Tuple(self.at(0, 0), self.at(0, 1), self.at(0, 2), self.at(0, 3));
  const auto row_2 = Tuple(self.at(1, 0), self.at(1, 1), self.at(1, 2), self.at(1, 3));
  const auto row_3 = Tuple(self.at(2, 0), self.at(2, 1), self.at(2, 2), self.at(2, 3));
  const auto row_4 = Tuple(self.at(3, 0), self.at(3, 1), self.at(3, 2), self.at(3, 3));

  return Tuple(dotProduct(row_1, tup), dotProduct(row_2, tup), dotProduct(row_3, tup), dotProduct(row_4, tup));
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
