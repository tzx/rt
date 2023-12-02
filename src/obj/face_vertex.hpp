#pragma once

#include <cstddef>

class FaceVertex {
  public:
    FaceVertex(size_t index, size_t tvi, size_t vni) {
      this->index_ = index;
      this->texture_vertex_index_ = tvi;
      this->vertex_normal_index_ = vni;
    }

    size_t index() const;
    size_t texture_vertex_index() const;
    size_t vertex_normal_index() const;

  private:
    // Since obj is 1-index we can use index 0 as the "null"
    size_t index_;
    // TODO: not used for now
    size_t texture_vertex_index_;
    size_t vertex_normal_index_;
};
