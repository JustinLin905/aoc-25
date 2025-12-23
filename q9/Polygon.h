#pragma once

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct Point {
  double x;
  double y;

  Point(double x, double y);
};

struct Segment {
  Point p1;
  Point p2;

  Segment(const Point &p1, const Point &p2);
};

class Polygon {
private:
  std::vector<Point> vertices;
  std::vector<Segment> edges;
  bool rayIntersectsEdge(const Point &point, const Segment &edge);

public:
  Polygon(const std::vector<Point> &points);
  bool hitTest(const Point &point);
  bool intersectsRectangle(const double rMinX, const double rMaxX,
                           const double rMinY, const double rMaxY);
};
