#pragma once

#include "../primitives/tuple.hpp"

class SmoothTriangle {
  public:
    SmoothTriangle(Tuple p1, Tuple p2, Tuple p3, Tuple n1, Tuple n2, Tuple n3) {
      this->p1_ = p1;
      this->p2_ = p2;
      this->p3_ = p3;
      this->n1_ = n1;
      this->n2_ = n2;
      this->n3_ = n3;
    };

    Tuple p1() const;
    Tuple p2() const;
    Tuple p3() const;
    Tuple n1() const;
    Tuple n2() const;
    Tuple n3() const;

  private:
    Tuple p1_;
    Tuple p2_;
    Tuple p3_;
    Tuple n1_;
    Tuple n2_;
    Tuple n3_;
};
