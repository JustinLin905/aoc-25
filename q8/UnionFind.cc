#include "UnionFind.h"
#include <vector>

UnionFind::UnionFind(int n) : parent(n), rank(n, 1), count(n) {
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
  }
}

int UnionFind::find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

bool UnionFind::join(int u, int v) {
  int rootU = find(u);
  int rootV = find(v);

  if (rootU == rootV) {
    // std::cout << "Already joined: " << u << " and " << v << std::endl;
    return false;
  }

  // Swap smaller rank into v
  if (rank[rootV] > rank[rootU]) {
    std::swap(rootU, rootV);
  }

  // Union
  parent[rootV] = rootU;
  rank[rootU] += rank[rootV];

  //   std::cout << "Newly joined: " << u << " and " << v << std::endl;
  count--;
  return true;
}

bool UnionFind::isConnected() { return count == 1; }

std::vector<int> UnionFind::getComponentSizes() {
  std::vector<int> sizes;
  for (int i = 0; i < parent.size(); ++i) {
    if (parent[i] == i) {
      sizes.push_back(rank[i]);
    }
  }
  return sizes;
}
