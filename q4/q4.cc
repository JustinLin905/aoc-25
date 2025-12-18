#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

// Constants
constexpr int ADJ_THRESHOLD = 4;

// Helper fn to count adjacent tiles that are rolls
int countAdjTiles(const vector<vector<char>> &graph, int r, int c) {
  static constexpr int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                     {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  int n = graph.size();
  int m = graph[r].size();

  int count = 0;

  for (auto &dir : dirs) {
    int row = r + dir[0];
    int col = c + dir[1];

    if (0 <= row && row < n && 0 <= col && col < m && graph[row][col] == '@') {
      count++;
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << " <multipleRounds? (y/n)>"
         << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  bool multipleRounds = argc == 3 && argv[2][0] == 'y' ? true : false;

  int totalRollCount = 0;
  int roundRollCount = 0; // How many rolls were removed this round

  vector<vector<char>> graph;

  if (in.is_open()) {
    // Ingest all lines to start
    while (getline(in, line)) {
      // Split line into chars and add to graph
      vector<char> newRow;
      for (char ch : line) {
        newRow.push_back(ch);
      }
      graph.push_back(newRow);
    }
    in.close();
  } else {
    cout << "Unable to open file error";
    return 1;
  }

  // Check each tile in graph
  do {
    roundRollCount = 0;

    for (int r = 0; r < graph.size(); r++) {
      for (int c = 0; c < graph[r].size(); c++) {
        if (graph[r][c] == '@' && countAdjTiles(graph, r, c) < ADJ_THRESHOLD) {
          roundRollCount++;
          totalRollCount++;

          // Remove roll now (if multiple rounds/roll removal is enabled)
          if (multipleRounds) {
            graph[r][c] = 'x';
          }
        }
      }
    }
  } while (multipleRounds && roundRollCount > 0);

  cout << "Output: " << totalRollCount << endl;
  return 0;
}
