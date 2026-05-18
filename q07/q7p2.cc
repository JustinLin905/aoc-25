#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

vector<vector<long long>> memo; // memoization table

long long dp(size_t r, size_t c, const vector<string> &graph) {
  if (memo[r][c] != -1) {
    return memo[r][c];
  }

  if (r == graph.size()) {
    // Path to bottom found
    return 1;
  }

  long long res = 0;
  if (graph[r][c] == '^') {
    res += dp(r + 1, c - 1, graph) + dp(r + 1, c + 1, graph);
  } else {
    res += dp(r + 1, c, graph);
  }

  memo[r][c] = res;
  return res;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  vector<string> graph;

  if (!in.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  // Ingest graph
  while (getline(in, line)) {
    graph.push_back(line);
  }
  in.close();

  size_t startCol = graph.front().find('S');
  unordered_set<size_t> activeBeams{startCol};

  // Note that tachyon splitters are never in adjacent cells in graph
  // Splitters are also never found on the end of rows
  memo.resize(
      graph.size() + 1,
      vector<long long>(graph[0].size(), -1LL)); // Initialize memo table
  cout << "Number of paths: " << dp(1, startCol, graph) << endl;
  return 0;
}
