#pragma once

#include "../primitives/matrix4.hpp"
#include "../primitives/tuple.hpp"

class Bounds {
  public:
    Bounds(Tuple min_, Tuple max_);

    Tuple maximum() const;
    Tuple minimum() const;

    void merge(const Bounds &oth);
    void make_fit(const Tuple &p);
    Bounds transform(const Mat4 &m);

    bool operator==(const Bounds &oth) const;

  private:
    Tuple maximum_;
    Tuple minimum_;
};
