#pragma once

class Tuple {
  private:
    float x;
    float y;
    float z;
    float w;
  public:
    Tuple() = default;
    Tuple(float x, float y, float z, float w);
    static Tuple create_point(float x, float y, float z);
    static Tuple create_vector(float x, float y, float z);

    bool isPoint() const;
    bool isVector() const;
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    float getMagnitude() const;
    Tuple getNormalized() const;
    void repr() const;

    bool operator==(const Tuple &other) const;
    Tuple operator+(const Tuple &other) const;
    Tuple operator-(const Tuple &other) const;
    Tuple operator-() const;
    Tuple operator*(const float &scalar) const;
    Tuple operator/(const float &scalar) const;
};

float dotProduct(const Tuple &a, const Tuple &b);
Tuple crossProduct(const Tuple &a, const Tuple &b);
