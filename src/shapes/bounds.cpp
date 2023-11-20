#include "bounds.hpp"

Bounds::Bounds(Tuple min_, Tuple max_) {
  this->minimum_ = min_;
  this->maximum_ = max_;
}

Tuple Bounds::minimum() const {
  return minimum_;
}

Tuple Bounds::maximum() const {
  return maximum_;
}
