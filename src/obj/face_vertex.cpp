#include "face_vertex.hpp"

size_t FaceVertex::index() const {
  return this->index_;
}

size_t FaceVertex::vertex_normal_index() const {
  return this->vertex_normal_index_;
}

size_t FaceVertex::texture_vertex_index() const {
  return this->texture_vertex_index_;
}
