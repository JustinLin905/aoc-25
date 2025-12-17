#include "ipow.h"
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

inline void sumInvalidIDs(long long intervalStart, long long intervalEnd,
                          long long &invalidSum, long long &count) {
  PRINT(cout << endl
             << "Start/End: " << intervalStart << "," << intervalEnd << endl);
  while (intervalStart <= intervalEnd) {
    long long len = intervalStart % 10 == 0 ? log10(intervalStart) + 1
                                            : ceil(log10(intervalStart));

    if (len % 2 != 0) {
      // Odd length: jump to next even-length value
      intervalStart = ipow(10, len);
      continue;
    }

    // Extract left half of number
    long long left = intervalStart / ipow(10, len / 2);
    long long mirror = (left * ipow(10, len / 2)) + left;

    // Mirror must fall in range
    if (intervalStart <= mirror && mirror <= intervalEnd) {
      PRINT(cout << "invalid ID found: " << mirror << endl);
      invalidSum += mirror;
      count++;
    }

    // Jump to next
    intervalStart = (left + 1) * ipow(10, len / 2);
  }
}
