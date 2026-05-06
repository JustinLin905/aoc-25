#pragma once
#include <cassert>
#include <cctype>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Region {
private:
  int width;
  int height;
  std::vector<int> counts;

public:
  Region(int width, int height) : width(width), height(height) {}
  void addRequirement(int requirement) { counts.push_back(requirement); }
  bool validate(const std::vector<int> &presentAreas) const {
    assert(counts.size() == presentAreas.size());

    int remainingArea = width * height;
    for (size_t i = 0; i < counts.size(); i++) {
      remainingArea -= counts[i] * presentAreas[i];
    };

    return remainingArea >= 0;
  }
};
