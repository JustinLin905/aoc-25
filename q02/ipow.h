/*
 * ipow.h
 * Fast exponentiation function, long long return type
 */

inline long long ipow(long long base, long long exp) {
  long long result = 1;
  while (exp > 0) {
    if (exp & 1)
      result *= base;
    base *= base;
    exp >>= 1;
  }
  return result;
}
