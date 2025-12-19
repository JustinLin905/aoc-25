#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>

using namespace std;

/**
 * @brief Sorts and merges a vector of overlapping intervals
 *
 * @param intervals A vector of intervals represented as pairs of long long
 * @return vector<pair<long long, long long>>: A vector of merged,
 * non-overlapping intervals
 */
vector<pair<long long, long long>>
mergeIntervals(vector<pair<long long, long long>> intervals) {
  vector<pair<long long, long long>> mergedIntervals;

  // Sort and merge intervals
  sort(intervals.begin(), intervals.end());
  mergedIntervals.push_back(intervals.front());

  for (int i = 1; i < intervals.size(); i++) {
    // If this interval's start overlaps with most recent interval's end
    // Sorting precludes case that incoming interval has a sooner start than
    // most recent interval
    if (intervals[i].first <= mergedIntervals.back().second) {
      mergedIntervals.back().second =
          max(intervals[i].second, mergedIntervals.back().second);
    } else {
      mergedIntervals.push_back(intervals[i]);
    }
  }

  return mergedIntervals;
}

/**
 * @brief Performs binary search on a vector of sorted, disjoint intervals
 *
 * @param id Long long integer
 * @param mergedIntervals A vector of intervals represented as pairs
 * @return bool: true if given id falls within any interval, false otherwise
 */
bool intervalBinarySearch(
    long long id, const vector<pair<long long, long long>> &mergedIntervals) {
  long long lo = 0;
  long long hi = mergedIntervals.size() - 1;

  while (lo <= hi) {
    long long m = lo + (hi - lo) / 2;
    // cout << "m: " << m << ", interval: " << mergedIntervals[m].first << ", "
    //      << mergedIntervals[m].second << endl;

    if (id < mergedIntervals[m].first) {
      // id falls before this interval
      hi = m - 1;
    } else if (id > mergedIntervals[m].second) {
      // id falls after this interval
      lo = m + 1;
    } else {
      // id falls within interval
      return true;
    }
  }

  return false;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string line;
  ifstream in(argv[1]);
  size_t numberBreak;

  vector<pair<long long, long long>> intervals;
  vector<pair<long long, long long>> mergedIntervals;
  int freshCount = 0;

  if (in.is_open()) {
    // Ingest intervals
    while (getline(in, line) && line != "") {
      long long intervalStart = stoll(line, &numberBreak);
      long long intervalEnd = stoll(line.substr(numberBreak + 1));
      intervals.push_back(
          pair<long long, long long>(intervalStart, intervalEnd));
    }

    // Sort and merge intervals
    mergedIntervals = mergeIntervals(intervals);

    // Ingest IDs
    while (getline(in, line)) {
      long long id = stoll(line);
      if (intervalBinarySearch(id, mergedIntervals)) {
        freshCount++;
      }
    }

    in.close();
  } else {
    cout << "Unable to open file error";
  }

  cout << "Output: " << freshCount << endl;
  return 0;
}
