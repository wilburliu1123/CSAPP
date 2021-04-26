#include <stdio.h>
long arith(long x, long y, long z) {
    long t1 = x + y;
    long t2 = z + t1;
    long t3 = x + 4;
    long t4 = y * 48;
    long t5 = t3 + t4;
    long rval = t2 * t5;
    return rval;
}

long test(long x) {
    x = x << 1 | 1;
    return x;
}
long test2(long x) {
    x = 2 * x + 1;
    return x;
}
