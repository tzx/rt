#pragma once

#include "../canvas/color.hpp"
#include "point_light.hpp"

class Material {
  public:
    Material();
    
    Color color() const;
    float ambient() const;
    float diffuse() const;
    float specular() const;
    float shininess() const;

    void setColor(Color c);
    void setAmbient(float a);
    void setDiffuse(float d);
    void setSpecular(float s);
    void setShininess(float s);

    Color lighting(PointLight light, Tuple point, Tuple eyev, Tuple normalv, bool in_shadow = false) const;

    bool operator==(const Material &oth) const;

  private:
    Color color_;
    float ambient_;
    float diffuse_;
    float specular_;
    float shininess_;
};
