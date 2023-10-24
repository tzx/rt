#pragma once

#include <vector>
#include "tuple.hpp"

class Matrix {
  private:
    int w_;
    int h_;
    std::vector<float> values_;
    inline int idx(int row, int col) const;

  public:
    Matrix(int width, int height, std::vector<float> values);
    static Matrix identity_matrix(int size);

    int width() const;
    int height() const;
    float& operator()(int row, int col);
    float at(int row, int col) const;

    Matrix transpose() const;
};

Matrix operator*(const Matrix &self, const Matrix &other);
Tuple operator*(const Matrix &self, const Tuple &tup);
bool operator==(const Matrix &self, const Matrix &other);
