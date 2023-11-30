#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "../primitives/tuple.hpp"
#include "face.hpp"

class ObjParser {
  public:
    ObjParser(std::string filename);

    const std::vector<std::shared_ptr<const Tuple>>& vertices() const;
    const std::vector<Face>& default_group() const;
    const std::vector<Face>& group(std::string group_name) const;
    size_t lines_ignored() const;

  private:
    std::vector<Face> default_group_;
    std::unordered_map<std::string, std::vector<Face>> groups_;
    std::vector<std::shared_ptr<const Tuple>> vertices_;
    size_t lines_ignored_;
};

Tuple parse_vertex(std::string& line);
std::vector<Face> parse_face(std::string &line, const std::vector<std::shared_ptr<const Tuple>> &vertices);
std::string parse_group(std::string &line);
