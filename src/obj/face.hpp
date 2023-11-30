#pragma once

#include <memory>

#include "../primitives/tuple.hpp"

namespace obj {
  using shared_vertex = std::shared_ptr<const Tuple>;
}

class Face {
  public:
    Face(obj::shared_vertex v1, obj::shared_vertex v2, obj::shared_vertex v3);

    obj::shared_vertex p1() const;
    obj::shared_vertex p2() const;
    obj::shared_vertex p3() const;

  private:
    obj::shared_vertex p1_;
    obj::shared_vertex p2_;
    obj::shared_vertex p3_;
};
