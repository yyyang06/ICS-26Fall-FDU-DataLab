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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(x&y)&~(~x&~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x>>31)&(~x+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int shift = dst << 3;
  int byte = (x >> (src << 3)) & 0xFF;
  int mask = 0xFF << shift;
  return (x & ~mask) | (byte << shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x>>n)&~(((1<<31)>>n)<<1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int maskF0 = (240 << 24) | (240 << 16) | (240 << 8) | 240;
  int mask0F = ~maskF0;
  return ((x & mask0F) << 4) | (((x & maskF0) >> 4)&~(~0xF<<24));
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int a=~x;
  int b=a&(a+(~0));
  return b^(b&(b+(~0)));
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  return ((x>>n)&~(((1<<31)>>n)<<1))|(x<<(32+~n+1));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int mask = (1 << n) + ~0;
  int half = 1 << (n + ~0);

  int q = x >> n;
  int r = x & mask;

  int greater = !((r + ~half) >> 31);
  int equal = !(r ^ half);

  int up = greater | (equal & (q & 1));

  return (q + up) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int mid = (x & y) + ((x ^ y) >> 1);
  int odd = (x ^ y) & 1;

  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int diffSign = ((x + (~y + 1)) >> 31) & 1;

  int greater = ((sx ^ sy) & (!sx)) | (!(sx ^ sy) & !diffSign & !!(x ^ y));

  return mid + (odd & greater);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = (x >> 31) & 1;
  int sa = (a >> 31) & 1;
  int sb = (b >> 31) & 1;

  int ax = sa ^ sx;
  int bx = sb ^ sx;

  int xa = ((x + (~a + 1)) >> 31) & 1;
  int xb = ((x + (~b + 1)) >> 31) & 1;

  int a_le_x = (ax & sa) | (!ax & !xa);
  int x_le_a = (ax & sx) | ((!ax) & (xa | !(x ^ a)));

  int b_le_x = (bx & sb) | (!bx & !xb);
  int x_le_b = (bx & sx) | ((!bx) & (xb | !(x ^ b)));

  return (a_le_x & x_le_b) | (b_le_x & x_le_a);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int sign = x >> 31;
    int ax = (x ^ sign) + (sign & 1);

    int limit = (0x19 << 24) |
                (0x99 << 16) |
                (0x99 << 8) | 0x99;

    int overflow = (ax >> 31) |
                   ~((ax + ~limit) >> 31);

    int tmin = 1 << 31;
    int sat = tmin ^ ~sign;

    int y = (x << 2) + x;

    return (overflow & sat) | (~overflow & y);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s = x + y;
  int t = s + z;

  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int sz = (z >> 31) & 1;
  int ss = (s >> 31) & 1;
  int st = (t >> 31) & 1;

  int pos1 = !sx & !sy & ss;
  int neg1 = sx & sy & !ss;

  int pos2 = !ss & !sz & st;
  int neg2 = ss & sz & !st;

  int pos = pos1 + pos2;
  int neg = neg1 + neg2;

  return pos + (~neg + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;

  if (exp == 255)
      return uf;

  if (exp == 0 && frac == 0)
      return uf;

  unsigned sig = frac;
  unsigned e = exp;

  if (exp != 0) {
      sig |= 1u << 23;
  } else {
      e = 1;
  }

  unsigned p = sig * 3u;
  unsigned shift = 1;

  if (p >= (1u << 25)) {
      shift = 2;
      e++;
  }

  unsigned q = p >> shift;
  unsigned mask = (1u << shift) - 1;
  unsigned rem = p & mask;
  unsigned half = 1u << (shift - 1);

  if (rem > half || (rem == half && (q & 1)))
      q++;

  if (q >= (1u << 24)) {
      q >>= 1;
      e++;
  }

  if (exp == 0 && q < (1u << 23))
      e = 0;

  if (e >= 255)
      return sign | 0x7F800000u;

  return sign | (e << 23) | (q & 0x7FFFFFu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xFFu;
    unsigned frac = uf & 0x7FFFFFu;

    if (exp == 255)
        return uf;

    if (exp < 126)
        return sign;

    if (exp == 126) {
        if (frac == 0)
            return sign;
        return sign | (127u << 23);
    }

    int e = (int)exp - 127;

    if (e >= 23)
        return uf;

    unsigned sig = (1u << 23) | frac;
    unsigned shift = 23 - e;

    unsigned mask = (1u << shift) - 1;
    unsigned rem = sig & mask;
    unsigned half = 1u << (shift - 1);

    unsigned integer = sig >> shift;

    if (rem > half ||
        (rem == half && (integer & 1))) {
        integer++;
    }

    unsigned result = integer << shift;

    if (result >= (1u << 24)) {
        exp++;
        result >>= 1;
    }

    return sign | (exp << 23) |
           (result & 0x7FFFFFu);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned abs_x = 0;
  unsigned temp;
  unsigned exp;
  unsigned frac;
  unsigned mask;
  unsigned round_bits;

  sign = (x >> 31) & (1<<31); 
  if (x==0) return 0;
  if (x>0||x<0) abs_x = (x ^ (x >> 31)) +(~ (x >> 31)+1);
  temp = abs_x;
  exp = 127 + 31; 
  mask = 1 << 31;
  while ((((temp & mask) >> 31) == 0) && temp) {
    temp <<= 1;
    exp+=~0;
  }
  frac = temp << 1 >> 9;
  round_bits = temp << 24; 
    if (round_bits > (1<<31)) {
        frac+=1;  
    }  
    if (round_bits == (1<<31)) {
        if (frac & 1) frac+=1;  
    }

    if (frac >> 23) {
        frac = 0;
        exp+=1;
    }

    return sign | (exp << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int m1_1 = (85<<8)|85;
    int m1 = (m1_1<<16)|m1_1;
    
    int m2_1 = 51;       
    int m2 = (m2_1 << 24) | (m2_1 << 16) | (m2_1 << 8) | m2_1;
    
    int m4_1 = 15;      
    int m4 = (m4_1 << 24) | (m4_1 << 16) | (m4_1 << 8) | m4_1;
    
    int m8_1 = 255;     
    int m8 = (m8_1 << 16) | m8_1;       
    int m16 = (m8_1 << 8) | m8_1;      
    
    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = (x & m8) + ((x >> 8) & m8);
    x = (x & m16) + ((x >> 16) & m16);
    return x;  
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m16=(255<<8)|255;
  int m8=m16^(m16<<8);
  int m4=m8^(m8<<4);
  int m2=m4^(m4<<2);
  int m1=m2^(m2<<1);


  x=((x & m1)<< 1)|((x >> 1) & m1);
  x=((x & m2)<< 2)|((x >> 2) & m2);
  x=((x & m4)<< 4)|((x >> 4) & m4);
  x=((x & m8)<< 8)|((x >> 8) & m8);
  x=(x<<16)|((x>>16)&m16);
  return x;
}
