#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "../primitives/tuple.hpp"
#include "../shapes/triangle.hpp"

class ObjParser {
  public:
    ObjParser(std::string filename);

    const std::vector<std::shared_ptr<const Tuple>>& vertices() const;
    const std::vector<Triangle>& default_group() const;
    const std::vector<Triangle>& group(std::string group_name) const;
    size_t lines_ignored() const;

    std::shared_ptr<Group> obj_to_group() const;

  private:
    std::vector<Triangle> default_group_;
    std::unordered_map<std::string, std::vector<Triangle>> groups_;
    std::vector<std::shared_ptr<const Tuple>> vertices_;
    size_t lines_ignored_;
};

Tuple parse_vertex(std::string& line);
std::vector<Triangle> parse_face(std::string &line, const std::vector<std::shared_ptr<const Tuple>> &vertices);
std::string parse_group(std::string &line);
