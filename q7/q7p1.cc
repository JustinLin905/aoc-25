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

using namespace std;

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

  size_t startIdx = graph.front().find('S');
  unordered_set<size_t> activeBeams{startIdx};
  int numberOfSplits = 0;

  // Note that tachyon splitters are never in adjacent cells in graph
  // Splitters are also never found on the end of rows
  for (size_t r = 1; r < graph.size(); r++) {
    unordered_set<size_t> nextBeams;

    for (const size_t &beam : activeBeams) {
      if (graph[r][beam] == '^') {
        // This beam encountered a splitter
        // Set handles duplicate columns
        numberOfSplits++;
        nextBeams.insert({beam - 1, beam + 1});
      } else {
        // Beam continues downwards
        nextBeams.insert(beam);
      }
    }

    activeBeams = nextBeams;
  }

  cout << "Number of splits: " << numberOfSplits << endl;
  cout << "Number of final beams: " << activeBeams.size() << endl;
  return 0;
}
