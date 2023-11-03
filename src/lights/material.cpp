#include "material.hpp"
#include <cmath>

Material::Material() {
  this->color_ = Color(1, 1, 1);
  this->ambient_ = 0.1;
  this->diffuse_ = 0.9;
  this->specular_ = 0.9;
  this->shininess_ = 200.0;
}

Color Material::color() const { return this->color_; }

void Material::setColor(Color c) { this->color_ = c; }

float Material::ambient() const { return this->ambient_; }

void Material::setAmbient(float a) { this->ambient_ = a; }

float Material::diffuse() const { return this->diffuse_; }

void Material::setDiffuse(float d) { this->diffuse_ = d; }

float Material::specular() const { return this->specular_; }

void Material::setSpecular(float s) { this->specular_ = s; }

float Material::shininess() const { return this->shininess_; }

void Material::setShininess(float s) { this->shininess_ = s; }

std::optional<StripePattern> Material::pattern() const {
  return this->pattern_;
}

void Material::setPattern(StripePattern pattern) {
  this->pattern_ = std::optional<StripePattern>(pattern);
}

Color Material::lighting(Shape *obj, PointLight light, Tuple point, Tuple eyev,
                         Tuple normalv, bool in_shadow) const {
  Color black = Color(0, 0, 0);

  Color col_to_use = this->color();
  if (this->pattern().has_value()) {
    col_to_use = this->pattern().value().stripe_at_object(obj, point);
  };

  Color effective_color = col_to_use * light.intensity();

  Tuple lightv = (light.position() - point).getNormalized();

  Color ambient = effective_color * this->ambient();

  if (in_shadow) {
    return ambient;
  }

  float light_dot_normal = dotProduct(lightv, normalv);

  Color diffuse;
  Color specular;
  if (light_dot_normal < 0) {
    diffuse = black;
    specular = black;
  } else {
    diffuse = effective_color * this->diffuse() * light_dot_normal;

    Tuple reflectv = reflect(-lightv, normalv);
    float reflect_dot_eye = dotProduct(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = black;
    } else {
      float factor = std::pow(reflect_dot_eye, this->shininess());
      specular = light.intensity() * this->specular() * factor;
    }
  }

  return ambient + diffuse + specular;
}

bool Material::operator==(const Material &oth) const {
  return this->color() == oth.color() && this->ambient() == oth.ambient() &&
         this->diffuse() == oth.diffuse() &&
         this->specular() == oth.specular() &&
         this->shininess() == oth.shininess();
}
