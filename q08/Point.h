#pragma once

#include <cmath>
#include <stdio.h>
#include <stdlib.h>

struct Point {
  double x;
  double y;
  double z;

  Point(double x, double y, double z) : x(x), y(y), z(z) {}
};

inline double euclideanDistance(const Point &p1, const Point &p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  double dz = p1.z - p2.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}
