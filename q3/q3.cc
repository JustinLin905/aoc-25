#include <algorithm>
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

#ifdef NOOUTPUT
#define PRINT(stmt)
#else
#define PRINT(stmt) stmt
#endif // NOOUTPUT

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  long long res;

  if (in.is_open()) {
    while (getline(in, line)) {
      // Always best to take largest first number (not in last position)
      // Tie-break with leftmost occurrence
      // Second character is largest from that point out
      auto firstIt = max_element(line.begin(), line.end() - 1);
      char maxFirstChar = *firstIt;
      auto secondIt = max_element(firstIt + 1, line.end());
      char maxSecondChar = *secondIt;

      // chars are '0'-'9'
      long long joltage = (maxFirstChar - '0') * 10 + (maxSecondChar - '0');
      res += joltage;
    }
    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << res << endl;
  return 0;
}
