#include "face.hpp"

Face::Face(obj::shared_vertex v1, obj::shared_vertex v2, obj::shared_vertex v3) {
  p1_ = v1;
  p2_ = v2;
  p3_ = v3;
}

obj::shared_vertex Face::p1() const {
  return this->p1_;
}

obj::shared_vertex Face::p2() const {
  return this->p2_;
}

obj::shared_vertex Face::p3() const {
  return this->p3_;
}
