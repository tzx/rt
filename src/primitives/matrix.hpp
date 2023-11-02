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
    static Matrix translation(float x, float y, float z);
    static Matrix scaling(float x, float y, float z);
    static Matrix rotation_x(float radians);
    static Matrix rotation_y(float radians);
    static Matrix rotation_z(float radians);
    static Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

    int width() const;
    int height() const;
    void repr() const;
    float determinant() const;
    float& operator()(int row, int col);
    float at(int row, int col) const;
    float minor(int row, int col) const;
    float cofactor(int row, int col) const;
    bool invertible() const;

    Matrix submatrix(int row, int col) const;
    Matrix transpose() const;
    Matrix inverse() const;
};

Matrix operator*(const Matrix &self, const Matrix &other);
Matrix operator*(const Matrix &self, const float cst);
Tuple operator*(const Matrix &self, const Tuple &tup);
bool operator==(const Matrix &self, const Matrix &other);

Matrix view_transform(const Tuple from, const Tuple to, const Tuple up);
