
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class UnionFind {
private:
  std::vector<int> parent;
  std::vector<int> rank;
  int count; // component count

public:
  UnionFind(int n);
  int find(int x);
  bool join(int u, int v);
  bool isConnected();
  std::vector<int> getComponentSizes();
};
