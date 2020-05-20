/* 
 * CS:APP Data Project
 * 
 * <Marni Rabinowitz rabin056>
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in on Canvas.
 *
 * WARNING: Do not include <stdio.h> or other headers; they will
 * confuse the dlc compiler. You can still use printf for debugging
 * without including <stdio.h>, because we've declared it below.
 */

int printf(const char *fmt, ...);

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Project by
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
  one operator per line. Notice however that all the lines that declare
  variables (the ones starting with "int") need to come before any lines that
  do not declare variables. Modern C and C++ compilers are more permissive
  in allowing declarations and statements to be intermixed, but you need to
  follow the strict separation of putting all the declarations first for
  compatibility with the DLC that checks the coding rules.

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
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only basic bitwise operations ~, |, and &.
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
/*int ones gets all the matched ones, int zeroes gets all the matched zeroes, and the return statment returns all the bits that match by combining matching ones and zeroes*/
  int ones = x & y;
  int zeroes = ~x & ~y;
  return ~(~ones & ~zeroes);
}
/* 
 * magicNumber - return the bit pattern 0xfff2ffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 */
int magicNumber(void) {
/*This function shifts a constant number 0xD0 left by 12 to get 0x000d0000, which is the negation of 0xfff2ffff*/
   return ~(0xD0 << 12);
}
/* 
 * copyLSByte - set all bytes of result to least significant byte of x
 *   Example: copyLSByte(5) = 0x05050505, copyLSByte(-2) = 0xfefefefe
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSByte(int x) {
/*int LSByte gets the least significant byte, and y and z shift LSByte the right amount to copy it to the rest of the number*/
int LSByte = (x & 0xff);
int y = LSByte | (LSByte<<8);
int z = y | (y<<16);
return z;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNonNegative(int x) {
/*This function gets the most significant bit and negates it because we want negative numbers (with most significant bit 1) to return 0 and positive (with most significant bit 0) to return 1 */
  return !(x >> 31);
}
/* 
 * isLowercase - return 1 if x as ASCII code is a lowercase letter.
 *   Example: isLowercase(0x35) = 0.
 *            isLowercase(0x61) = 1.
 *            isLowercase(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isLowercase(int x) {
/*Lowercase ASCII letters range from 0x61 to 0x7A, so this function checks if x is in that range*/
  int lower, upper;
  lower = x + (~0x60);
  lower = lower >> 31;

  upper = 0x7b + ~x;
  upper = upper >> 31;

  return !(lower|upper);
}
/*
 * isUppercaseConsonant - return 1 if x as an ASCII code is an uppercase
 *     letter, but not a vowel A, E, I, O, or U. As an exception to the usual
 *     rules for integer problems, you may use any integer constants, even
 *     big ones.
 *   Example: isUppercaseConsonant(0x35) = 0. ('5')
 *            isUppercaseConsonant(0x4D) = 1. ('M')
 *            isUppercaseConsonant(0x55) = 0. ('U')
 *            isUppercaseConsonant(0x59) = 1. ('Y')
 *   Legal ops: ! ~ & ^ | + << >>, also large constants
 *   Max ops: 15
 *   Rating: 3
 */
int isUppercaseConsonant(int x) {
/*This function first checks if x is in the range of uppercase ASCII letters (0x41 to 0x5B) and then uses a bit mask to check if x is a vowel or not*/
  int y,z, shift, mask, sh, ans;
y = x + (~0x40);
  y = y >> 31;

  z = 0x5B + ~x;
  z = z >> 31;

  ans = !(y|z);
mask = 0xFC104111;
sh = x + ~0x40;
shift = ((mask >> sh) ^ 1);
return  shift & ans;
}
/*
 * satUMul3 - multiplies by 3, saturating to UMax if unsigned overflow
 *  Examples: satUMul3(0x10000000) = 0x30000000
 *            satUMul3(0x50000000) = 0xf0000000
 *            satUMul3(0x60000000) = 0xFFFFFFFF (Saturate to UMax)
 *            satUMul3(0xFFFFFFFF) = 0xFFFFFFFF (Saturate to UMax)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satUMul3(int x) {
/*This function checks if x is between the upper bound and lower bound for unsigned numbers, and returns x*3 if it is, and UMax if it is not*/
int add3 = x+x+x;
int first = 170 | (170 << 8);
int second = first | (first << 16);
int low = x + second;
int high = (x >> 31);
return (low >> 31 & ~high & add3) | ~(low >> 31 & ~high);
}
/* 
 * floatUChar2Float - Return bit-level equivalent of expression (float) x,
 *   where x is an unsigned char between 0 and 255.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 4
 */
unsigned floatUChar2Float(unsigned char b) {
  unsigned frac, shift, shiftHelper;  
  unsigned X, Y, Z;
  unsigned ex = 31;
  unsigned temp; 
 
  if (b == 0) {
    return 0;
  }

  while((b & (1<<ex)) == 0) {
    ex--;
  }

  if (ex >= 23) {
    temp = ex-23;
    shift = temp;
    shiftHelper = 1 << (shift - 1);
    X = b & (1 << shift);
    Y = b & (shiftHelper);
    Z = b & ((shiftHelper) - 1);

    frac = b >> (temp);

    if ((Y && Z) || (Y && X)) {
      frac += 1;
    }
  } else {
    frac = b << (23 - ex);
  }

  return ((ex + 127) << 23) | (frac & 0x7fffff);
}


/* Inside this comment, cut and paste the final report obtained from
   running "perl check.pl" showing how your assigned was auto-graded:

 
Correctness Results	Perf Results
Points	Rating	Errors	Points	Ops	Puzzle
1	1	0	2	8	bitMatch
1	1	0	2	2	magicNumber
2	2	0	2	5	copyLSByte
2	2	0	2	2	isNonNegative
3	3	0	2	8	isLowercase
3	3	0	2	13	isUppercaseConsonant
3	3	0	2	17	satUMul3
4	4	0	2	25	floatUChar2Float

Raw Score = 35/35 [19/19 Corr + 16/16 Perf] (80 total operators)

Username: rabin056
Host: csel-vole-31.cselabs.umn.edu
Time: Fri May  1 20:31:58 2020
bits.c checksum: 344db2e1d8fa65fcda77698e2d2a0424e3a524b4

Scaled auto-grading score = 70/70

Report checksum: 3d2a725868d0da95c733883fb7b5514889239201

*/
