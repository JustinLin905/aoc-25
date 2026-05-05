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
const string START = "you";
const string END = "out";
} // namespace constants

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

  // Start DAG traversal at node "you"
  auto result = 0;
  queue<string> q{{constants::START}};

  for (; !q.empty(); q.pop()) {
    string curNode = q.front();

    if (curNode == constants::END) {
      result++;
      continue;
    }

    // For each adjacent
    for (const auto &adj : graph[curNode]) {
      q.push(adj);
    }
  }

  cout << "Output: " << result << endl;
  return 0;
}
