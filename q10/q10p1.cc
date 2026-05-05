#include <cctype>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>

using namespace std;

// Helper fn to extract binary number from binary string
int binaryStringToInt(string binaryStr, char high) {
  int res = 0;

  for (size_t i = 0; i < binaryStr.size(); i++) {
    res <<= 1;

    if (binaryStr[i] == high) {
      res |= 1;
    }
  }

  return res;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  int totalRequiredPushes = 0;

  if (!in.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  while (getline(in, line)) {
    stringstream ss(line);

    // For each new line, we need a new DP table
    vector<vector<long long>> dp;
    int targetState = 0;
    int stateLen = 0; // Length needed to represent states in bits
    int numButtons = 0;
    vector<int> buttons;

    // Process each string separated by whitespace
    string chunk;
    while (ss >> chunk) {
      if (chunk[0] == '[') {
        string stateStr = chunk.substr(1, chunk.size() - 2);
        stateLen = stateStr.size();
        targetState = binaryStringToInt(stateStr, '#');
      } else if (chunk[0] == '(') {
        numButtons++;

        // Extract each comma-separated int
        stringstream bss(chunk.substr(1, chunk.size() - 2));
        int newButton = 0;
        string token;

        while (getline(bss, token, ',')) {
          int lightIdx = stoi(token);
          newButton |= (1 << (stateLen - lightIdx - 1));
        }

        buttons.push_back(newButton);
      } else if (chunk[0] == '{') {
        // P2 will be completed in a separate .cc file because I am curious
        // about measuring timing
      }
    }

    // DP for this line
    dp.resize(numButtons + 1, vector<long long>(1 << stateLen, INT_MAX));

    // Set first column to 0 (you can trivially reach the starting state 0, with
    // all lights off)
    for (int r = 0; r <= numButtons; r++) {
      dp[r][0] = 0;
    }

    for (int idx = 1; idx < dp.size(); idx++) {
      int button = buttons[idx - 1];

      for (int state = 0; state < dp[idx].size(); state++) {
        // Minimum cost to reach this state comes either from not pressing
        // current button, or pressing the current button
        // We must get the previous state if we pressed this button, found by
        // toggling every associated light
        int prevState = state ^ button;
        dp[idx][state] = min(dp[idx - 1][state], dp[idx - 1][prevState] + 1);
      }
    }

    totalRequiredPushes += dp[numButtons][targetState];
  }
  in.close();

  cout << "P1: " << totalRequiredPushes << endl;
  return 0;
}
