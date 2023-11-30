#include "obj_parser.hpp"
#include "face.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

ObjParser::ObjParser(std::string filename) {
  // make it 1-index
  this->vertices_.push_back(std::shared_ptr<Tuple>());
  this->lines_ignored_ = 0;

  std::string line;
  std::ifstream file(filename);
  std::string current_group;
  while (std::getline(file, line)) {
    if (line.front() != 'v' && line.front() != 'f' && line.front() != 'g') {
      this->lines_ignored_ += 1;
      continue;
    }

    char cmd = line.at(0);
    line.erase(0, 2);

    if (cmd == 'v') {
      auto pt = std::make_shared<const Tuple>(parse_vertex(line));
      this->vertices_.push_back(pt);
    } else if (cmd == 'f') {
      auto triangles = parse_face(line, this->vertices_);
      for (auto tri: triangles) {
        this->default_group_.push_back(tri);
        if (current_group == "") {
          continue;
        }
        this->groups_[current_group].push_back(tri);
      }
    } else if (cmd == 'g') {
      current_group = parse_group(line);
      this->groups_[current_group] = {};
    }
  }
}

size_t ObjParser::lines_ignored() const { return this->lines_ignored_; }

const std::vector<std::shared_ptr<const Tuple>> &ObjParser::vertices() const {
  return this->vertices_;
}

const std::vector<Triangle> &ObjParser::default_group() const {
  return this->default_group_;
}

const std::vector<Triangle>& ObjParser::group(std::string group_name) const {
  auto it = this->groups_.find(group_name);
  if (it == this->groups_.end()) {
    static std::vector<Triangle> nullresult;
    return nullresult;
  }
  return it->second;
}

// All parse helpers assume that the line already removed the first token
Tuple parse_vertex(std::string &line) {
  size_t pos = 0;
  std::string token;
  std::vector<float> points;
  while ((pos = line.find(' ')) != std::string::npos) {
    token = line.substr(0, pos);
    float f = std::stof(token);
    points.push_back(f);
    line.erase(0, pos + 1);
  }
  float f = std::stof(line);
  points.push_back(f);

  assert(points.size() == 3);
  Tuple pt = Tuple::create_point(points.at(0), points.at(1), points.at(2));
  return pt;
}

std::vector<Triangle> parse_face(std::string &line,
                const std::vector<std::shared_ptr<const Tuple>> &vertices) {
  size_t pos = 0;
  std::string token;
  std::vector<size_t> indices;
  while ((pos = line.find(' ')) != std::string::npos) {
    token = line.substr(0, pos);
    size_t index = std::stoull(token);
    indices.push_back(index);
    line.erase(0, pos + 1);
  }
  size_t index = std::stoull(line);
  indices.push_back(index);

  std::vector<Triangle> triangles;
  for (auto i = 1; i < indices.size() - 1; ++i) {
    Triangle tri = Triangle(
      *vertices.at(indices.at(0)),
      *vertices.at(indices.at(i)),
      *vertices.at(indices.at(i + 1))
    );
    triangles.push_back(tri);
  }

  return triangles;
}

std::string parse_group(std::string &line) {
  return line;
}
