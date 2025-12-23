#include "q9.h"
#include "Polygon.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  vector<Point> points;
  double maxArea = 0;
  double maxRedGreenArea = 0;

  if (!in.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  while (getline(in, line)) {
    stringstream ss(line);
    double x, y;
    char comma;

    ss >> x >> comma >> y;
    points.emplace_back(x, y);
  }
  in.close();

  // Part 1
  for (size_t p1 = 0; p1 < points.size(); p1++) {
    for (size_t p2 = p1 + 1; p2 < points.size(); p2++) {
      double run = abs(points[p1].x - points[p2].x) + 1;
      double rise = abs(points[p1].y - points[p2].y) + 1;
      maxArea = max(rise * run, maxArea);
    }
  }

  // Part 2
  Polygon polygon(points);
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      Point p1 = points[i];
      Point p2 = points[j];

      double run = abs(p1.x - p2.x) + 1;
      double rise = abs(p1.y - p2.y) + 1;
      double area = run * rise;

      // Optimization
      if (area <= maxRedGreenArea) {
        continue;
      }

      double rMinX = std::min(p1.x, p2.x);
      double rMaxX = std::max(p1.x, p2.x);
      double rMinY = std::min(p1.y, p2.y);
      double rMaxY = std::max(p1.y, p2.y);

      // Interior point test
      if (polygon.hitTest(Point(rMinX + 0.5, rMinY + 0.5))) {
        // Check for edge intersections
        if (!polygon.intersectsRectangle(rMinX, rMaxX, rMinY, rMaxY)) {
          maxRedGreenArea = max(area, maxRedGreenArea);
        }
      }
    }
  }

  // Hit test testing
  //   Point inside(9, 2);
  //   Point on(5, 5);
  //   Point outside(13, 6);

  //   assert(polygon.hitTest(inside));
  //   assert(polygon.hitTest(on));
  //   assert(!polygon.hitTest(outside));

  cout << "P1: " << static_cast<long long>(maxArea) << endl;
  cout << "P2: " << static_cast<long long>(maxRedGreenArea) << endl;

  return 0;
}
