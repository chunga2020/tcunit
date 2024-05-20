#include <tcunit/tests/math.h>
#include <tcunit/dbg.h>
#include <errno.h>

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int divide(int a, int b)
{
    check(b != 0, "Division by zero");

    return a / b;
 error:
    return EINVAL;
}

int myremainder(int a, int b)
{
    check(b != 0, "Division by zero");
    int quotient = a / b;

    return a - (quotient * b);

 error:
    return EINVAL;
}
