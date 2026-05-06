#include "Region.h"
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>

using namespace std;

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

  vector<int> presentAreas;
  vector<Region> regions;

  while (getline(in, line)) {
    regex nextPresentRegex("^\\d+:$");
    regex areaRegex("^(\\d+)x(\\d+): (.*)");
    smatch match;

    if (regex_match(line, nextPresentRegex)) {
      auto presentArea = 0;
      string presentLine;

      while (getline(in, presentLine)) {
        if (presentLine.empty()) {
          break;
        }

        // Count #'s on line
        presentArea += count(presentLine.begin(), presentLine.end(), '#');
      }

      presentAreas.push_back(presentArea);
    } else if (regex_match(line, match, areaRegex)) {
      Region r{stoi(match[1]), stoi(match[2])};
      string reqs = match[3];
      stringstream ss(reqs);
      int req;
      while (ss >> req) {
        r.addRequirement(req);
      }
      regions.push_back(r);
    }
  }
  in.close();

  // Validate each region against present areas
  auto result = 0;
  for (const auto &r : regions) {
    if (r.validate(presentAreas)) {
      result++;
    }
  }

  cout << "Output: " << result << endl;
  return 0;
}
