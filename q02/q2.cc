#ifdef USE_HEADER
#include USE_HEADER
#else
#include "q2p1.h"
#endif

using namespace std;

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

        sumInvalidIDs(intervalStart, intervalEnd, invalidSum, count);
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
