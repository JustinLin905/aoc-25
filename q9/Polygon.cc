#include "Polygon.h"
#include <algorithm>
#include <iostream>

Point::Point(double x, double y) : x(x), y(y) {}

Segment::Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

// Assume ray is a horizontal line to x = -1 from point of interest
// With ray.p1.x == -1
// Also note it is impossible for ray to intersect with two vertical segments in
// this problem
// Notice how std::min(edge.p1.y, edge.p2.y) < ray.p1.y does not include
// equality: this is to avoid double counting
bool Polygon::rayIntersectsEdge(const Point &point, const Segment &edge) {
  // Construct ray
  const Point left(-1, point.y);
  const Segment ray(left, point);

  if (edge.p1.x == edge.p2.x && std::min(edge.p1.y, edge.p2.y) < ray.p1.y &&
      ray.p1.y <= std::max(edge.p1.y, edge.p2.y) && ray.p2.x > edge.p1.x) {
    return true;
  }

  // Vertical edge did not intersect or edge is horizontal
  // We do not count horizontal intersections to avoid double counting
  return false;
}

Polygon::Polygon(const std::vector<Point> &points) : vertices(points) {
  // Create bounding edges
  for (size_t i = 0; i < vertices.size(); i++) {
    const Point p1 = vertices[i];
    const Point p2 = vertices[(i + 1) % vertices.size()];
    edges.emplace_back(p1, p2);
  }
}

// Used to test if point is strictly inside polygon
bool Polygon::hitTest(const Point &point) {
  int intersectionCount = std::count_if(edges.begin(), edges.end(),
                                        [this, &point](const Segment &edge) {
                                          return rayIntersectsEdge(point, edge);
                                        });

  // If number of intersections with vertical edges is odd, the point was within
  // the polygon
  if (intersectionCount & 1) {
    // std::cout << "Point (" << point.x << ", " << point.y
    //           << ") is inside the polygon with count: " << intersectionCount
    //           << std::endl;
    return true;
  } else {
    // std::cout << "Point (" << point.x << ", " << point.y
    //           << ") is outside the polygon with count: " << intersectionCount
    //           << std::endl;
    return false;
  }
}

// If any edge strictly intersects with the interior of the rectangle, then the
// rectangle is not fully contained within the polygon.
// The inverse is not necessarily true: we need to do an interior point test
// (see main)
// Touching the edges of the rectangle does not count as an intersection
bool Polygon::intersectsRectangle(const double rMinX, const double rMaxX,
                                  const double rMinY, const double rMaxY) {
  for (const Segment &edge : edges) {
    if (edge.p1.x == edge.p2.x) {
      // Vertical edge
      double edgeX = edge.p1.x;
      double edgeYMin = std::min(edge.p1.y, edge.p2.y);
      double edgeYMax = std::max(edge.p1.y, edge.p2.y);
      if (rMinX < edgeX && edgeX < rMaxX) {
        double overlapMin = std::max(rMinY, edgeYMin);
        double overlapMax = std::min(rMaxY, edgeYMax);
        if (overlapMin < overlapMax) {
          return true;
        }
      }
    } else {
      // Horizontal edge
      double edgeY = edge.p1.y;
      double edgeXMin = std::min(edge.p1.x, edge.p2.x);
      double edgeXMax = std::max(edge.p1.x, edge.p2.x);
      if (rMinY < edgeY && edgeY < rMaxY) {
        double overlapMin = std::max(rMinX, edgeXMin);
        double overlapMax = std::min(rMaxX, edgeXMax);
        if (overlapMin < overlapMax) {
          return true;
        }
      }
    }
  }

  return false;
}
