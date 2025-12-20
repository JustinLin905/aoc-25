#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>

using namespace std;

void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
            return !std::isspace(c);
          }));
}

long long concatDigitToInt(long long num, long long digit) {
  return num * 10 + digit;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  vector<string> lines;

  long long grandTotal = 0;

  if (in.is_open()) {
    while (getline(in, line)) {
      lines.push_back(line);
    }
    in.close();

    vector<long long> columnOperands;
    long long nextOperand;

    // Assume all lines have equal length
    int read_ptr = lines[0].size() - 1;

    while (read_ptr >= 0) {
      // Add next column operand
      nextOperand = 0;

      // Iterate over each operand row
      for (int r = 0; r < lines.size() - 1; r++) {
        if (!isspace(lines[r][read_ptr])) {
          nextOperand = concatDigitToInt(nextOperand, lines[r][read_ptr] - '0');
        }
      }

      columnOperands.push_back(nextOperand);

      // Operator will be present in last column of this equation
      if (lines.back()[read_ptr] == '+') {
        // Add each column operand to grandTotal
        grandTotal +=
            accumulate(columnOperands.begin(), columnOperands.end(), 0LL);

        // Reset column operands and decrement an extra time to skip whitespace
        // column
        columnOperands.clear();
        read_ptr--;
      } else if (lines.back()[read_ptr] == '*') {
        // Add product
        grandTotal += accumulate(columnOperands.begin(), columnOperands.end(),
                                 1LL, multiplies<long long>());
        columnOperands.clear();
        read_ptr--;
      }

      // Always decrement read pointer
      read_ptr--;
    }
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << grandTotal << endl;
  return 0;
}
