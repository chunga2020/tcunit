#ifndef tcunit_test_math_h
#define tcunit_test_math_h

/* A trivial set of functions to just test tcunit */

/*
 * Add two integers.
 *
 * Parameters:
 * a: the first addend.
 * b: the second addend.
 *
 * Return:
 * Returns the sum of a and b.
 */
int add(int a, int b);

/*
 * Subtract two integers.
 *
 * Parameters:
 * a: the minuend.
 * b: the subtrahend.
 *
 * Return:
 * Returns the difference of a and b.
 * */
int subtract(int a, int b);

/*
 * Divide two integers.
 *
 * Parameters:
 * a: the dividend.
 * b: the divisor.
 *
 * Return:
 * Returns the quotient of a / b.
 */
int divide(int a, int b);

/*
 * Compute the remainder of an integer division.
 *
 * Parameters:
 * a: the dividend.
 * b: the divisor.
 *
 * Return:
 * Returns the remainder of the interger division a / b.
 */
int myremainder(int a, int b);

#endif
