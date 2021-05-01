#include <stdio.h>

void multstore(long, long, long *);

int allOddBits(int x) {
  int oddSet = 0xAAAAAAAA;
  return !(~x & oddSet);
}
int mybitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
int isTmax(int x) {
  int min = 1 << 31;
  return !(~x ^ min);
}
int isAsciiDigit(int x) {
  int low = 0x30;
  int high = 0x39;
  int lowerBound = x + ~low + 1;
  int sign1 = lowerBound >> 31 & 1;
  int higherBound = high + ~x + 1;
  int sign2 = higherBound >> 31 & 1;
  return !sign1 & !sign2;
}
int isLessOrEqual(int x, int y) {
  int neg = 1 << 31;
  return !(((x + ~y + 1) ^ neg) >> 31) + !(x + ~y + 1);
}
int logicalNeg(int x) {
  int union_set = (x | (~x + 1)) >> 31;  // 0 only if x is 0, otherwise union_set is -1
  return union_set + 1;
}
int main() {
    // long d;
    // multstore(2, 3, &d);
    // printf("2 * 3 --> %ld\n", d);
      int min = 1 << 31;
      int x = 0x55;
      int myres = logicalNeg(-1234);
    //   int test = 0x55;
    //   printf("This should be max: %d\n", (!test));
      printf("min is: %d\n", ~0x7fffffff & min);
      printf("myres: %d\n", myres);
      printf("x is: %d\n", x);
    printf("%d\n", !(x & ~min));
    return 0;
}

long mult2(long a, long b) {
    long s = a * b;
    return s;
}