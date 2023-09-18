#pragma once

class Tuple {
  private:
    float x;
    float y;
    float z;
    float w;
    Tuple(float x, float y, float z, float w);
  public:
    static Tuple create_point(float x, float y, float z);
    static Tuple create_vector(float x, float y, float z);

    void repr();
};
