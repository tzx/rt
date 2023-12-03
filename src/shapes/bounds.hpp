#pragma once

#include "../primitives/matrix4.hpp"
#include "../primitives/tuple.hpp"

class Bounds {
  public:
    constexpr Bounds(Tuple min_, Tuple max_) :
      minimum_(min_),
      maximum_(max_) {}

    constexpr const Tuple& maximum() const { return this->maximum_; }
    constexpr const Tuple& minimum() const { return this->minimum_; }

    void merge(const Bounds &oth);
    void make_fit(const Tuple &p);
    Bounds transform(const Mat4 &m);

    constexpr bool operator==(const Bounds &oth) const {
      return minimum() == oth.minimum() && maximum() == oth.maximum();
    }

  private:
    Tuple maximum_;
    Tuple minimum_;
};
