#ifndef ANGLES_H
#define ANGLES_H

#include <cmath>

static const float pi = std::acos(-1);

struct Radians {
  float value = 0.f;

  float ToDegrees() const { return value * (180.f / pi); }
};

struct Degrees {
  float value = 0.f;

  float ToRadians() const { return value * (pi / 180.f); }
};

#endif
