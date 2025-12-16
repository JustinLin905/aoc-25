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
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);

  if (in.is_open()) {
    while (getline(in, line)) {
    }
    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << endl;
  return 0;
}
