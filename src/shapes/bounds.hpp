#pragma once

#include "../primitives/tuple.hpp"

class Bounds {
  public:
    Bounds(Tuple min_, Tuple max_);

    Tuple maximum() const;
    Tuple minimum() const;

  private:
    Tuple maximum_;
    Tuple minimum_;
};
