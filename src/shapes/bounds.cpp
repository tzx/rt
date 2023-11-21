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

bool Bounds::operator==(const Bounds &oth) const {
  return minimum() == oth.minimum() && maximum() == oth.maximum();
}

void Bounds::merge(const Bounds &oth) {
  const auto oth_min = oth.minimum();
  const auto oth_max = oth.maximum();
  minimum_ = Tuple::create_point(std::min(oth_min.getX(), minimum_.getX()),
                                 std::min(oth_min.getY(), minimum_.getY()),
                                 std::min(oth_min.getZ(), minimum_.getZ()));
  maximum_ = Tuple::create_point(std::max(oth_max.getX(), maximum_.getX()),
                                 std::max(oth_max.getY(), maximum_.getY()),
                                 std::max(oth_max.getZ(), maximum_.getZ()));
}

void Bounds::make_fit(const Tuple &p) {
  // TODO: this is kinda weird because of we are technically also using the object space coordinates as bounds
  // while we can/should be using only the transformed into parent space coordinates
  // This is fine though, it will just a make a bigger box that always(?) contains the world origin
  minimum_ = Tuple::create_point(std::min(p.getX(), minimum_.getX()),
                                 std::min(p.getY(), minimum_.getY()),
                                 std::min(p.getZ(), minimum_.getZ()));
  maximum_ = Tuple::create_point(std::max(p.getX(), maximum_.getX()),
                                 std::max(p.getY(), maximum_.getY()),
                                 std::max(p.getZ(), maximum_.getZ()));
}

Bounds Bounds::transform(Matrix m) {
  // Transform the bounding box by changing all 8 of the corners
  // using make_fit for the new bounding_box
  const auto mi = minimum();
  const auto ma = maximum();

  make_fit(m * mi);
  make_fit(m * Tuple::create_point(mi.getX(), mi.getY(), ma.getZ()));
  make_fit(m * Tuple::create_point(mi.getX(), ma.getY(), ma.getZ()));
  make_fit(m * Tuple::create_point(mi.getX(), ma.getY(), mi.getZ()));

  make_fit(m * Tuple::create_point(ma.getX(), mi.getY(), ma.getZ()));
  make_fit(m * Tuple::create_point(ma.getX(), mi.getY(), mi.getZ()));
  make_fit(m * Tuple::create_point(ma.getX(), ma.getY(), mi.getZ()));
  make_fit(m * ma);

  return *this;
}
