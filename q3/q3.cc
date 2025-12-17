#include <algorithm>
#include <cassert>
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

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " <filename>" << " <batteryCount>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  long long res = 0;

  int batteryCount = stoi(argv[2]); // Battery count per row
  char selectedBatteries[batteryCount];

  string::iterator it;
  if (in.is_open()) {
    while (getline(in, line)) {
      string::iterator start = line.begin();

      for (int i = 0; i < batteryCount; i++) {
        it = max_element(start, line.end() - (batteryCount - i - 1));
        selectedBatteries[i] = *it; // Select this battery

        start = it + 1; // Start selection range for next character strictly
        // after the chosen character
      }

      long long rowJoltage = 0;
      for (int i = 0; i < batteryCount; i++) {
        // chars are '0'-'9'
        rowJoltage = (rowJoltage * 10) + (selectedBatteries[i] - '0');
      }
      res += rowJoltage;
    }

    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << res << endl;
  return 0;
}
