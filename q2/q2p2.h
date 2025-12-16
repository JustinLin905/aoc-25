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
  long long id = intervalStart;
  while (id <= intervalEnd) {
    long long len = id % 10 == 0 ? log10(id) + 1 : ceil(log10(id));

    for (int step = 1; step <= len / 2; step++) {
      //   PRINT(cout << "Trying step size " << step << " on id " << id <<
      //   endl;)
      long long chunk = -1;
      long long cur = id;
      bool invalidId = true;

      while (cur > 0) {
        long long nextChunk = cur % (ipow(10, step));
        // PRINT(cout << "chunk: " << chunk << ", nextChunk: " << nextChunk
        //            << endl;)

        if (chunk != -1 && (chunk != nextChunk || chunk < ipow(10, step - 1))) {
          invalidId = false;
          break;
        }

        chunk = nextChunk;
        cur /= ipow(10, step);
      }

      // If id is divisible into sequence of digits repeated at least twice
      if (invalidId) {
        PRINT(cout << "***Invalid ID found: " << id << endl;)
        invalidSum += id;
        count++;
        break;
      }
    }

    // Try next id
    id++;
  }
}
