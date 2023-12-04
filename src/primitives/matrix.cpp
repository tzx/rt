#include "matrix.hpp"
#include "../util/approx.hpp"
#include "tuple.hpp"
#include <cassert>
#include <iostream>
#include <ostream>

Matrix::Matrix(int height, int width, std::vector<float> values) {
  w_ = width;
  h_ = height;
  values_ = std::vector<float>(w_ * h_);

  for (size_t i = 0; i < values.size(); ++i) {
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

void Matrix::repr() const {
  for (auto r = 0; r < this->height(); ++r) {
    for (auto c = 0; c < this->width(); ++c) {
      std::cout << this->at(r, c) << ", ";
    }
    std::cout << std::endl;
  }
}

inline int Matrix::idx(int row, int col) const {
  return row * w_ + col;
}

float Matrix::determinant() const {
  assert(this->width() == this->height());

  if (this->width() == 2 && this->height() == 2) {
    return this->at(0, 0) * this->at(1, 1) - this->at(0, 1) * this->at(1, 0);
  } else {
    float sum = 0.0f;
    // Use first row for the cofactors
    for (auto col = 0; col < this->width(); ++col) {
      float val = this->at(0, col);
      sum += val * cofactor(0, col);
    }
    return sum;
  }
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

Matrix Matrix::submatrix(int row, int col) const {
  std::vector<float> new_values;
  for (auto r = 0; r < this->height(); ++r) {
    for (auto c = 0; c < this->width(); ++c) {
      if (row == r || c == col) {
        continue;
      }
      new_values.push_back(this->at(r, c));
    }
  }
  return Matrix(this->height() - 1, this->width() - 1, new_values);
}

Matrix Matrix::inverse() const {
  auto det = this->determinant();
  // -> cofactor matrix -> transpose -> times 1/(original det)
  std::vector<float> cofactor_values;

  for (auto r = 0; r < this->height(); ++r) {
    for (auto c = 0; c < this->width(); ++c) {
      cofactor_values.push_back(this->cofactor(r, c));
    }
  }

  Matrix cofactor_m = Matrix(this->height(), this->width(), cofactor_values);
  Matrix res = cofactor_m.transpose() * (1.0f/det);
  return res;
}

float Matrix::minor(int row, int col) const {
  Matrix sub = this->submatrix(row, col);
  return sub.determinant();
}

// + - + 
// - + -
// + - +
// r + c = odd -> negate
float Matrix::cofactor(int row, int col) const {
  auto minor = this->minor(row, col);
  if ((row + col) % 2 == 1) {
    minor = -minor;
  }
  return minor;
}

bool Matrix::invertible() const {
  return !approx_eq(this->determinant(), 0);
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

Matrix operator*(const Matrix &self, const float cst) {
  Matrix res = Matrix(self.height(), self.width(), {});
  for (auto r = 0; r < self.height(); ++r) {
    for (auto c = 0; c < self.width(); ++c) {
      res(r, c) = cst * self.at(r, c);
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

Matrix view_transform(const Tuple from, const Tuple to, const Tuple up) {
  Tuple forward = (to - from).getNormalized();
  Tuple left = crossProduct(forward, up.getNormalized());
  Tuple true_up = crossProduct(left, forward);

  std::vector<float> values = { left.getX(), left.getY(), left.getZ(), 0,
                                true_up.getX(), true_up.getY(), true_up.getZ(), 0,
                                -forward.getX(), -forward.getY(), -forward.getZ(), 0,
                                0, 0, 0, 1};
  Matrix orientation = Matrix(4, 4, values);

  return orientation * Matrix::translation(-from.getX(), -from.getY(), -from.getZ());
}
