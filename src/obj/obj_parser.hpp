#pragma once

#include "../primitives/tuple.hpp"
#include "../shapes/triangle.hpp"
#include "face_vertex.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ObjParser {
public:
  ObjParser(std::string filename);

  const std::vector<std::shared_ptr<const Tuple>> &vertices() const;
  const std::vector<std::shared_ptr<Triangle>> &default_group() const;
  const std::vector<std::shared_ptr<Triangle>> &
  group(std::string group_name) const;
  const std::vector<Tuple> &normals() const;
  size_t lines_ignored() const;

  std::shared_ptr<Group> obj_to_group() const;

private:
  std::vector<std::shared_ptr<Triangle>> default_group_;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Triangle>>>
      groups_;
  std::vector<std::shared_ptr<const Tuple>> vertices_;
  std::vector<Tuple> normals_;
  size_t lines_ignored_;
};

std::string parse_cmd(std::string &line);
Tuple parse_vertex(std::string &line);
std::vector<std::shared_ptr<Triangle>>
parse_face(std::string &line,
           const std::vector<std::shared_ptr<const Tuple>> &vertices,
           const std::vector<Tuple> &normals);
FaceVertex parse_face_vertex(std::string &token);
std::string parse_group(std::string &line);
