#pragma once

#include <vector>

class Matrix {
  private:
    int w_;
    int h_;
    std::vector<float> values_;
    inline int idx(int row, int col) const;

  public:
    Matrix(int width, int height, std::vector<float> values);
    int width() const;
    int height() const;
    float& operator()(int row, int col);
    float at(int row, int col) const;
};

bool operator==(const Matrix &self, const Matrix &other);
Matrix operator*(const Matrix &self, const Matrix &other);
