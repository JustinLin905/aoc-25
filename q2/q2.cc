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

long long ipow(long long base, long long exp) {
  long long result = 1;
  while (exp > 0) {
    if (exp & 1)
      result *= base;
    base *= base;
    exp >>= 1;
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  long long invalidSum = 0;
  long long count = 0;

  if (in.is_open()) {
    while (getline(in, line)) {
      stringstream ss(line);
      string token;

      long long intervalStart, intervalEnd;
      size_t numberBreak;

      while (getline(ss, token, ',')) {
        intervalStart = stoll(token, &numberBreak);
        intervalEnd = stoll(token.substr(numberBreak + 1));

        cout << endl
             << "Start/End: " << intervalStart << "," << intervalEnd << endl;
        long long counter = intervalStart;
        while (counter <= intervalEnd) {
          long long len =
              counter % 10 == 0 ? log10(counter) + 1 : ceil(log10(counter));

          if (len % 2 != 0) {
            // Odd length: jump to next even-length value
            counter = ipow(10, len);
            continue;
          }

          // Extract left half of number
          long long left = counter / ipow(10, len / 2);
          long long mirror = (left * ipow(10, len / 2)) + left;

          // Mirror must fall in range
          if (intervalStart <= mirror && mirror <= intervalEnd) {
            cout << "invalid ID found: " << mirror << endl;
            invalidSum += mirror;
            count++;
          }

          // Jump to next
          counter = (left + 1) * ipow(10, len / 2);
        }
      }
    }
    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Invalid Sum: " << invalidSum << endl;
  cout << "Invalid Count: " << count << endl;
  return 0;
}
