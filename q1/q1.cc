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

void applyRotationP1(int &dial, unsigned int &res, char direction, int amount) {
  if (direction == 'R') {
    dial = (dial + amount) % DIAL_MAX;
  } else {
    int diff = (dial - amount) % DIAL_MAX;
    dial = diff >= 0 ? diff : DIAL_MAX + diff; // + since diff is negative
  }

  if (dial == 0)
    res++;
}

void applyRotationP2(int &dial, unsigned int &res, char direction, int amount) {
  unsigned int turns_past_zero = 0;
  amount = direction == 'R' ? amount : amount * -1;

  dial += amount;

  if (dial >= DIAL_MAX) {
    turns_past_zero = dial / DIAL_MAX;
  } else if (dial < 0) {
    if (dial == amount) {
      // dial was 0 before applying the rotation
      turns_past_zero = abs(dial / DIAL_MAX);
    } else {
      turns_past_zero = abs(dial / DIAL_MAX) + 1;
    }
  } else if (dial == 0) {
    // dial is zero after rotation
    turns_past_zero = 1;
  }

  res += turns_past_zero;

  // Adjust dial to be 0-99
  dial %= DIAL_MAX;
  if (dial < 0)
    dial += DIAL_MAX;
}

int main() {
  string line;
  ifstream in("q1.txt");

  int dial = 50;
  unsigned int res = 0;

  if (in.is_open()) {
    while (getline(in, line)) {
      char direction = line[0];
      int amount = stoi(line.substr(1));

      // applyRotationP1(dial, res, direction, amount);
      applyRotationP2(dial, res, direction, amount);
    }
    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << res << endl;
  return 0;
}
