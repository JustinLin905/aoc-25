#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

// Global constants
const int DIAL_MAX = 100;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);

  int dial = 50;
  unsigned int res = 0;

  auto rotator = [&dial](int amount) {
    int next = dial + (amount % 100);
    int turns = ((dial > 0 && next <= 0 || next >= 100) + abs(amount) / 100);
    // dial = (next + 100) % 100;
    dial = next < 0 ? DIAL_MAX + (next % DIAL_MAX) : next % DIAL_MAX;
    return turns;
  };

  if (in.is_open()) {
    while (getline(in, line)) {
      char direction = line[0];
      int amount = stoi(line.substr(1));

      // applyRotationP1(dial, res, direction, amount);
      res += rotator(direction == 'R' ? amount : -amount);
    }
    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << res << endl;
  return 0;
}
