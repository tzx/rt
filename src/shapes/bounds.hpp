#pragma once

#include "../primitives/matrix.hpp"
#include "../primitives/tuple.hpp"

class Bounds {
  public:
    Bounds(Tuple min_, Tuple max_);

    Tuple maximum() const;
    Tuple minimum() const;

    void merge(const Bounds &oth);
    void make_fit(const Tuple &p);
    Bounds transform(Matrix m);

  private:
    Tuple maximum_;
    Tuple minimum_;
};
