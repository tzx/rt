#include "primitives/tuple.hpp"

class Ray {
  public:
    Ray(Tuple origin_, Tuple direction_);
    Tuple origin() const;
    Tuple direction() const;

  private:
    Tuple orig_;
    Tuple dir_;
};
