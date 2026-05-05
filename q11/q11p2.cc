#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

namespace constants {
const string START = "svr";
const string END = "out";
const string DAC = "dac";
const string FFT = "fft";
} // namespace constants

// size_t is used to avoid silent overflow
size_t dfs(const string &curNode, bool dac, bool fft,
           const unordered_map<string, vector<string>> &graph,
           unordered_map<string, size_t> &memo) {

  const auto key = curNode + (dac ? "1" : "0") + (fft ? "1" : "0");
  if (memo.find(key) != memo.end()) {
    return memo[key];
  }

  if (curNode == constants::END) {
    return dac && fft ? 1 : 0;
  }

  size_t result = 0;
  // For each adjacent
  for (const auto &adj : graph.at(curNode)) {
    result += dfs(adj, dac || adj == constants::DAC,
                  fft || adj == constants::FFT, graph, memo);
  }

  memo[key] = result;
  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);

  if (!in.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  // Construct graph
  unordered_map<string, vector<string>> graph;

  while (getline(in, line)) {
    auto pos = line.find(':');
    string sourceNode = line.substr(0, pos);

    graph[sourceNode] = vector<string>();

    // Read arbitrary number of adjacent nodes
    istringstream iss(line.substr(pos + 2));
    string adjacentNode;

    while (iss >> adjacentNode) {
      graph[sourceNode].push_back(adjacentNode);
    }
  }
  in.close();

  // Start DAG traversal at node "svr"
  auto memo = unordered_map<string, size_t>();
  cout << "Output: " << dfs(constants::START, false, false, graph, memo)
       << endl;
  return 0;
}
