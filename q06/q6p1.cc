#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
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
  vector<vector<long long>> operands;
  vector<char> operators;

  long long ans = 0; // For intermediate answers
  long long grandTotal = 0;

  if (in.is_open()) {
    while (getline(in, line)) {
      ltrim(line);
      if (isdigit(line[0])) {
        // Ingest new row of operands
        istringstream iss(line);
        vector<long long> row;
        long long x;

        while (iss >> x) {
          row.push_back(x);
        }
        operands.push_back(row);
      } else {
        // Ingest operator row
        istringstream iss(line);
        char op;

        while (iss >> op) {
          operators.push_back(op);
        }
      }
    }
    in.close();

    // Compute answers in each column
    for (int c = 0; c < operators.size(); c++) {
      char op = operators[c];
      ans = op == '+' ? 0 : 1;

      for (int r = 0; r < operands.size(); r++) {
        long long operand = operands[r][c];

        if (op == '+') {
          ans += operand;
        } else if (op == '*') {
          ans *= operand;
        }
      }

      grandTotal += ans;
    }
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << grandTotal << endl;
  return 0;
}
