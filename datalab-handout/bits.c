/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 * 1001 x
 * 0001 y
 * 0110
 * 1110 -> ~(x & y)
 *          &
 * 1001 -> ~(~x & ~y)
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */ 
int isTmax(int x) {
  int min = 1 << 31;
  return !(~x ^ min);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int oddSet = 0xAAAAAAAA;
  return !(~x & oddSet);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int low = 0x30;
  int high = 0x39;
  int lowerBound = x + ~low + 1;
  int sign1 = lowerBound >> 31 & 1;
  int higherBound = high + ~x + 1;
  int sign2 = higherBound >> 31 & 1;
  return !sign1 & !sign2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int union_set = (x | (~x + 1)) >> 31; //union set will only be 0 if x is 0
  int resY = union_set & y;
  int resZ = ~union_set & z;
  return resY + resZ;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int signX = x >> 31 & 1;
  int signY = y >> 31 & 1;
  int signY_x = (y + ~x + 1) >> 31 & 1; //sign of y - x;
  return (signX & !signY) | ((!(signX ^ signY)) & !signY_x);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int union_set = (x | (~x + 1)) >> 31;  // 0 only if x is 0, otherwise union_set is -1
  return union_set + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int negSign = (x >> 31) & 1;
  int union_set = ((negSign | (~negSign + 1)) >> 31); //union set is all one if negSign is 1, 0 otherwise
  int res1 = ~x & union_set; // get all one's if x is neg, otherwise 0
  int res2 = x & (~union_set); // get all one's if x is pos, otherwise 0
  int newX = res1 + res2; // one of res1 and res2 will be 0 and we will take the result and assign it to newX
  // need to simulate in order to understand
  int allOne = newX | newX >> 16;
  allOne = allOne | allOne >> 8;
  allOne = allOne | allOne >> 4;
  allOne = allOne | allOne >> 2;
  allOne = allOne | allOne >> 1;
  //count
  int count = (allOne & 0x55555555) + ((allOne >> 1) & 0x55555555); //0x55 is 0101 0101
  count = (count & 0x33333333) + ((count >> 2) & 0x33333333);  // 0x33 = 00110011
  count = (count & 0x0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f);  // 0x0f0f = 0000111100001111
  count = (count & 0x00ff00ff) + ((count >> 8) & 0x00ff00ff);  // 0x00ff = 0000000011111111
  count = (count & 0x0000ffff) + ((count >> 16) & 0x0000ffff); // this gives last 16 bits of 1

  return count + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  if (((uf >> 23) & 0xff) == 0xff) {
    return uf; // exp value in float representation are 1111 (infinity or NaN)
  }
  if (uf == 0 || uf == (1 << 31)) return uf; //0 or -(2^31) overflow for neg
  // denormalized
  if (((uf >> 23) & 0xff) == 0x00) {
    return ((uf & 0x007fffff) << 1) | ((1 << 31) & uf); 
  }
  return uf + (1 << 23); // normalized value
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {  
  int sign = uf >> 31 & 1; //get sign
  int e = (uf >> 23) & 0xff; //get exponent bit representation
  int exp = e - 127; // 8 bits only has max of 127, if larger, we will round it to zero
  int frac = uf & 0x7fffff; //get last 23 bits from fractional field of float number
  int nFrac = 0x1000000 + frac;
  if (exp < 0 || e == 0) return 0;
  if (exp >= 31 || e == 0xff) return 0x80000000; // check for overflow or infinity or NaN
  int res;
  if (exp > 24) {
    res = nFrac << (exp - 24);
  } else {
    res = nFrac >> (24 - exp);
  }

  if (sign) {
    res = -res;
  }

  return res;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x. 
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if (x < -150) {
      return 0;
    }
    if (x >= -150 && x <= -127) {
      int shift = (-x - 127);
      int frac = 1 << shift;
      return frac;
    }
    //normalized
    if (x >= -126 && x <= 127) {
      int e = (x + 127) << 23;
      return e;
    }
    if (x >= 128) {
      int e = 0xff << 23;
      return e;
    }
    return 0;
}
