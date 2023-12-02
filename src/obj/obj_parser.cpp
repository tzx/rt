#include "obj_parser.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

#include "../shapes/group.hpp"
#include "../shapes/smooth_triangle.hpp"

// TODO: maybe refactor? the old face to triangle

ObjParser::ObjParser(std::string filename) {
  // make it 1-index
  this->vertices_.push_back(std::shared_ptr<Tuple>());
  this->normals_.push_back(Tuple::create_vector(0, 0, 0));
  this->lines_ignored_ = 0;

  std::string line;
  std::ifstream file(filename);
  std::string current_group;
  while (std::getline(file, line)) {
    if (line.front() != 'v' && line.front() != 'f' && line.front() != 'g') {
      this->lines_ignored_ += 1;
      continue;
    }

    std::string cmd = parse_cmd(line);

    if (cmd == "vn") {
      auto pt = parse_vertex(line);
      pt.turnIntoVector();
      this->normals_.push_back(pt);
    } else if (cmd == "v") {
      auto pt = std::make_shared<const Tuple>(parse_vertex(line));
      this->vertices_.push_back(pt);
    } else if (cmd == "f") {
      auto triangles = parse_face(line, this->vertices_, this->normals_);
      for (auto tri: triangles) {
        this->default_group_.push_back(tri);
        if (current_group == "") {
          continue;
        }
        this->groups_[current_group].push_back(tri);
      }
    } else if (cmd == "g") {
      current_group = parse_group(line);
      this->groups_[current_group] = {};
    }
  }
}

size_t ObjParser::lines_ignored() const { return this->lines_ignored_; }

const std::vector<std::shared_ptr<const Tuple>> &ObjParser::vertices() const {
  return this->vertices_;
}

const std::vector<Tuple>& ObjParser::normals() const {
  return this->normals_;
}

const std::vector<std::shared_ptr<Triangle>> &ObjParser::default_group() const {
  return this->default_group_;
}

const std::vector<std::shared_ptr<Triangle>>& ObjParser::group(std::string group_name) const {
  auto it = this->groups_.find(group_name);
  if (it == this->groups_.end()) {
    static std::vector<std::shared_ptr<Triangle>> nullresult;
    return nullresult;
  }
  return it->second;
}

std::shared_ptr<Group> ObjParser::obj_to_group() const {
  auto super_group = std::make_shared<Group>();
  for (auto &[g_name, triangles]: this->groups_) {
    auto ggroup = std::make_shared<Group>();
    for (auto &tri: triangles) {
      ggroup->add_child(tri);
    }
    if (triangles.size() == 0) {
      continue;
    }
    super_group->add_child(ggroup);
  }

  if (!this->groups_.empty()) {
    return super_group;
  }

  auto ggroup = std::make_shared<Group>();
  for (auto &tri: this->default_group_) {
    ggroup->add_child(tri);
  }
  super_group->add_child(ggroup);
  return super_group;
}

std::string parse_cmd(std::string &line) {
  std::string cmd;
  size_t pos = line.find(' ');
  if (pos == std::string::npos) {
    return cmd;
  }
  cmd = line.substr(0, pos);
  line.erase(0, pos + 1);
  return cmd;
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

std::vector<std::shared_ptr<Triangle>> parse_face(std::string &line,
                const std::vector<std::shared_ptr<const Tuple>> &vertices,
                const std::vector<Tuple> &normals) {
  size_t pos = 0;
  std::string token;
  std::vector<FaceVertex> fvs;
  while ((pos = line.find(' ')) != std::string::npos) {
    token = line.substr(0, pos);
    FaceVertex fv = parse_face_vertex(token);
    fvs.push_back(fv);
    line.erase(0, pos + 1);
  }
  FaceVertex fv = parse_face_vertex(line);
  fvs.push_back(fv);

  std::vector<std::shared_ptr<Triangle>> triangles;

  for (auto i = 1; i < fvs.size() - 1; ++i) {
    auto vn0 = fvs.at(0).vertex_normal_index();
    auto vni = fvs.at(i).vertex_normal_index();
    auto vni1 = fvs.at(i + 1).vertex_normal_index();
    if (vn0 == 0 && vni == 0 && vni1 == 0) {
      auto tri = std::make_shared<Triangle>(
        *vertices.at(fvs.at(0).index()),
        *vertices.at(fvs.at(i).index()),
        *vertices.at(fvs.at(i + 1).index())
      );
      triangles.push_back(tri);
    } else {
      auto tri = std::make_shared<SmoothTriangle>(
        *vertices.at(fvs.at(0).index()),
        *vertices.at(fvs.at(i).index()),
        *vertices.at(fvs.at(i + 1).index()),
        normals.at(fvs.at(0).vertex_normal_index()),
        normals.at(fvs.at(i).vertex_normal_index()),
        normals.at(fvs.at(i + 1).vertex_normal_index())
      );
      triangles.push_back(tri);
    }
  }

  return triangles;
}

FaceVertex parse_face_vertex(std::string &token) {
  if (token.find('/') == std::string::npos) {
    size_t index = std::stoull(token);
    return FaceVertex(index, 0, 0);
  }
  size_t vertex, texture_vertex, vertex_normal = 0;
  std::stringstream ss = std::stringstream(token);
  std::string fv;
  if (std::getline(ss, fv, '/')) {
    if (!fv.empty()) {
      vertex = stoull(fv);
    }
  }

  if (std::getline(ss, fv, '/')) {
    if (!fv.empty()) {
      texture_vertex = stoull(fv);
    }
  }

  if (std::getline(ss, fv, '/')) {
    if (!fv.empty()) {
      vertex_normal = stoull(fv);
    }
  }
  return FaceVertex(vertex, texture_vertex, vertex_normal);
}

std::string parse_group(std::string &line) {
  return line;
}
