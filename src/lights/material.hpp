#pragma once

#include "../canvas/color.hpp"
#include "point_light.hpp"
#include "../patterns/stripe_pattern.hpp"
#include <memory>
#include <optional>

class Material {
  public:
    Material();
    
    Color color() const;
    float ambient() const;
    float diffuse() const;
    float specular() const;
    float shininess() const;
    float reflective() const;
    std::optional<std::shared_ptr<Pattern>> pattern() const;

    void setColor(Color c);
    void setAmbient(float a);
    void setDiffuse(float d);
    void setSpecular(float s);
    void setShininess(float s);
    void setReflective(float r);
    void setPattern(std::shared_ptr<Pattern> pattern);

    Color lighting(Shape *obj,
                   PointLight light,
                   Tuple point,
                   Tuple eyev,
                   Tuple normalv,
                   bool in_shadow = false) const;

    bool operator==(const Material &oth) const;

  private:
    Color color_;
    float ambient_;
    float diffuse_;
    float specular_;
    float shininess_;
    float reflective_;
    std::optional<std::shared_ptr<Pattern>> pattern_;
};
