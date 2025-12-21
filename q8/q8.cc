#include "q8.h"
#include <algorithm>
#include <utility>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename> <rounds?>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  vector<Point> points;
  vector<pair<double, pair<int, int>>> adj; // (weight, (id1, id2))

  long long product = 1;          // p1
  long long finalJoinProduct = 1; // p2

  if (!in.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  while (getline(in, line)) {
    stringstream ss(line);
    double x, y, z;
    char comma;

    ss >> x >> comma >> y >> comma >> z;
    points.emplace_back(x, y, z);
  }
  in.close();

  // Complete graph
  int n = points.size();
  for (int cur = 0; cur < n; cur++) {
    for (int next = cur + 1; next < n; next++) {
      double weight = euclideanDistance(points[cur], points[next]);
      adj.push_back({weight, {cur, next}});
    }
  }

  // Sort edges by weight
  sort(adj.begin(), adj.end());

  // Kruskal's
  UnionFind uf(n);

  int totalRounds = argc >= 3 ? stoi(argv[2]) : adj.size();
  for (int i = 0; i < totalRounds; i++) {
    int u = adj[i].second.first;
    int v = adj[i].second.second;

    uf.join(u, v);

    if (uf.isConnected()) {
      // Find answer for P2: product of X coordinates
      finalJoinProduct = points[u].x * points[v].x;
      break;
    }
  }

  vector<int> componentSizes = uf.getComponentSizes();
  nth_element(componentSizes.begin(), componentSizes.end() - 3,
              componentSizes.end());

  // P1: Multiply last 3 elements, which contain the sizes of the 3 largest
  // components
  size_t start = componentSizes.size() > 3 ? componentSizes.size() - 3 : 0;
  for (auto it = componentSizes.begin() + start; it != componentSizes.end();
       ++it) {
    product *= *it;
  }

  cout << "P1: " << product << endl;
  cout << "P2: " << finalJoinProduct << endl;
  return 0;
}
