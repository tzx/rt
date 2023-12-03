#pragma once

#include "tuple.hpp"
#include <cassert>
#include <cstdint>

constexpr int f(float x) { return 5; }

class Mat4 {
public:
  void repr() const;

  // Hopefully this meta programs right?
  constexpr float at(const uint8_t row, const uint8_t col) const {
    if (row == 0) {
      return get_col(col).getX();
    } else if (row == 1) {
      return get_col(col).getY();
    } else if (row == 2) {
      return get_col(col).getZ();
    } else {
      assert(row == 3);
      return get_col(col).getW();
    }
  }

  constexpr int height() const { return 4; }
  constexpr int width() const { return 4; }

  constexpr Mat4(const Tuple &c0, const Tuple &c1, const Tuple &c2,
                 const Tuple &c3)
      : col0_(c0), col1_(c1), col2_(c2), col3_(c3) {}

  constexpr static Mat4 identity_matrix() {
    constexpr auto c0 = Tuple(1, 0, 0, 0);
    constexpr auto c1 = Tuple(0, 1, 0, 0);
    constexpr auto c2 = Tuple(0, 0, 1, 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 translation(const float x, const float y,
                                    const float z) {
    constexpr auto c0 = Tuple(1, 0, 0, 0);
    constexpr auto c1 = Tuple(0, 1, 0, 0);
    constexpr auto c2 = Tuple(0, 0, 1, 0);
    const auto c3 = Tuple(x, y, z, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 scaling(const float x, const float y, const float z) {
    const auto c0 = Tuple(x, 0, 0, 0);
    const auto c1 = Tuple(0, y, 0, 0);
    const auto c2 = Tuple(0, 0, z, 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 rotation_x(const float r) {
    constexpr auto c0 = Tuple(1, 0, 0, 0);
    const auto c1 = Tuple(0, std::cos(r), std::sin(r), 0);
    const auto c2 = Tuple(0, -std::sin(r), std::cos(r), 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 rotation_y(const float r) {
    const auto c0 = Tuple(std::cos(r), 0, -std::sin(r), 0);
    constexpr auto c1 = Tuple(0, 1, 0, 0);
    const auto c2 = Tuple(std::sin(r), 0, std::cos(r), 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 rotation_z(const float r) {
    const auto c0 = Tuple(std::cos(r), std::sin(r), 0, 0);
    const auto c1 = Tuple(-std::sin(r), std::cos(r), 0, 0);
    constexpr auto c2 = Tuple(0, 0, 1, 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr static Mat4 shearing(const float xy, const float xz, const float yx,
                                 const float yz, const float zx,
                                 const float zy) {
    const auto c0 = Tuple(1, yx, zx, 0);
    const auto c1 = Tuple(xy, 1, zy, 0);
    const auto c2 = Tuple(xz, yz, 1, 0);
    constexpr auto c3 = Tuple(0, 0, 0, 1);
    return Mat4(c0, c1, c2, c3);
  }

  constexpr Mat4 inverse() const {
    // Calc adjoint
    const auto dst0 = +at(5) * at(10) * at(15) - at(5) * at(11) * at(14) -
                      at(9) * at(6) * at(15) + at(9) * at(7) * at(14) +
                      at(13) * at(6) * at(11) - at(13) * at(7) * at(10);

    const auto dst1 = -at(1) * at(10) * at(15) + at(1) * at(11) * at(14) +
                      at(9) * at(2) * at(15) - at(9) * at(3) * at(14) -
                      at(13) * at(2) * at(11) + at(13) * at(3) * at(10);

    const auto dst2 = +at(1) * at(6) * at(15) - at(1) * at(7) * at(14) -
                      at(5) * at(2) * at(15) + at(5) * at(3) * at(14) +
                      at(13) * at(2) * at(7) - at(13) * at(3) * at(6);

    const auto dst3 = -at(1) * at(6) * at(11) + at(1) * at(7) * at(10) +
                      at(5) * at(2) * at(11) - at(5) * at(3) * at(10) -
                      at(9) * at(2) * at(7) + at(9) * at(3) * at(6);

    const auto dst4 = -at(4) * at(10) * at(15) + at(4) * at(11) * at(14) +
                      at(8) * at(6) * at(15) - at(8) * at(7) * at(14) -
                      at(12) * at(6) * at(11) + at(12) * at(7) * at(10);

    const auto dst5 = +at(0) * at(10) * at(15) - at(0) * at(11) * at(14) -
                      at(8) * at(2) * at(15) + at(8) * at(3) * at(14) +
                      at(12) * at(2) * at(11) - at(12) * at(3) * at(10);

    const auto dst6 = -at(0) * at(6) * at(15) + at(0) * at(7) * at(14) +
                      at(4) * at(2) * at(15) - at(4) * at(3) * at(14) -
                      at(12) * at(2) * at(7) + at(12) * at(3) * at(6);

    const auto dst7 = +at(0) * at(6) * at(11) - at(0) * at(7) * at(10) -
                      at(4) * at(2) * at(11) + at(4) * at(3) * at(10) +
                      at(8) * at(2) * at(7) - at(8) * at(3) * at(6);

    const auto dst8 = +at(4) * at(9) * at(15) - at(4) * at(11) * at(13) -
                      at(8) * at(5) * at(15) + at(8) * at(7) * at(13) +
                      at(12) * at(5) * at(11) - at(12) * at(7) * at(9);

    const auto dst9 = -at(0) * at(9) * at(15) + at(0) * at(11) * at(13) +
                      at(8) * at(1) * at(15) - at(8) * at(3) * at(13) -
                      at(12) * at(1) * at(11) + at(12) * at(3) * at(9);

    const auto dst10 = +at(0) * at(5) * at(15) - at(0) * at(7) * at(13) -
                       at(4) * at(1) * at(15) + at(4) * at(3) * at(13) +
                       at(12) * at(1) * at(7) - at(12) * at(3) * at(5);

    const auto dst11 = -at(0) * at(5) * at(11) + at(0) * at(7) * at(9) +
                       at(4) * at(1) * at(11) - at(4) * at(3) * at(9) -
                       at(8) * at(1) * at(7) + at(8) * at(3) * at(5);

    const auto dst12 = -at(4) * at(9) * at(14) + at(4) * at(10) * at(13) +
                       at(8) * at(5) * at(14) - at(8) * at(6) * at(13) -
                       at(12) * at(5) * at(10) + at(12) * at(6) * at(9);

    const auto dst13 = +at(0) * at(9) * at(14) - at(0) * at(10) * at(13) -
                       at(8) * at(1) * at(14) + at(8) * at(2) * at(13) +
                       at(12) * at(1) * at(10) - at(12) * at(2) * at(9);

    const auto dst14 = -at(0) * at(5) * at(14) + at(0) * at(6) * at(13) +
                       at(4) * at(1) * at(14) - at(4) * at(2) * at(13) -
                       at(12) * at(1) * at(6) + at(12) * at(2) * at(5);

    const auto dst15 = +at(0) * at(5) * at(10) - at(0) * at(6) * at(9) -
                       at(4) * at(1) * at(10) + at(4) * at(2) * at(9) +
                       at(8) * at(1) * at(6) - at(8) * at(2) * at(5);

     const float det_i = + at(0) * dst0 
                      + at(1) * dst4
                      + at(2) * dst8
                      + at(3) * dst12;
     const float det = 1.0f / det_i;

     const auto c0 = Tuple(det * dst0, det * dst1, det * dst2, det * dst3);
     const auto c1 = Tuple(det * dst4, det * dst5, det * dst6, det * dst7);
     const auto c2 = Tuple(det * dst8, det * dst9, det * dst10, det * dst11);
     const auto c3 = Tuple(det * dst12, det * dst13, det * dst14, det * dst15);
     return Mat4(c0, c1, c2, c3);
  }

  constexpr Mat4 transpose() const {
    const auto c0 = Tuple(this->at(0, 0), at(0, 1), at(0, 2), at(0, 3));
    const auto c1 = Tuple(this->at(1, 0), at(1, 1), at(1, 2), at(1, 3));
    const auto c2 = Tuple(this->at(2, 0), at(2, 1), at(2, 2), at(2, 3));
    const auto c3 = Tuple(this->at(3, 0), at(3, 1), at(3, 2), at(3, 3));
    return Mat4(c0, c1, c2, c3);
  }

  constexpr Tuple operator*(const Tuple &t) const {
    auto c0 = this->col0_ * t.getX();
    auto c1 = this->col1_ * t.getY();
    auto c2 = this->col2_ * t.getZ();
    auto c3 = this->col3_ * t.getW();
    return c0 + c1 + c2 + c3;
  }

  constexpr Mat4 operator*(const Mat4 &other) const {
    auto c0 = *this * other.col0_;
    auto c1 = *this * other.col1_;
    auto c2 = *this * other.col2_;
    auto c3 = *this * other.col3_;
    return Mat4(c0, c1, c2, c3);
  }

private:
  Tuple col0_;
  Tuple col1_;
  Tuple col2_;
  Tuple col3_;

  constexpr const Tuple &get_col(const uint8_t col) const {
    if (col == 0) {
      return col0_;
    } else if (col == 1) {
      return col1_;
    } else if (col == 2) {
      return col2_;
    } else {
      assert(col == 3);
      return col3_;
    }
  }

  constexpr float at(const uint8_t idx) const {
    uint8_t col = idx / 4;
    uint8_t row = idx % 4;
    return at(row, col);
  }
};

constexpr bool operator==(const Mat4 &self, const Mat4 &other) {
  for (auto r = 0; r < self.height(); ++r) {
    for (auto c = 0; c < self.width(); ++c) {
      if (!approx_eq(self.at(r, c), other.at(r, c))) {
        return false;
      }
    }
  }
  return true;
}
