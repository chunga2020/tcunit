#include <errno.h>
#include <stdio.h>
#include <tcunit/tcunit.h>
#include <tcunit/dbg.h>

#include <tcunit/tests/math.h>

tc_Result test_add()
{
    tc_Result result = {.code = TC_OK};

    int a = 5;
    int b = 5;
    int expect = 10;
    int actual = add(a, b);

    tc_assert(actual == expect,
              "Adding %d and %d failed.  Expected %d.  Actual %d",
              a, b, expect, actual);

    return result;
}

tc_Result test_add_fail()
{
    tc_Result result = {.code=TC_OK};

    int a = 5;
    int b = 15;
    int expect = 20;
    int actual = add(a, b);

    tc_assert(actual == expect,
              "Adding %d and %d failed.  Expected %d.  Actual %d",
              a, b, expect, actual);

    return result;
}

tc_Result test_divide_zero()
{
    tc_Result result = {.code = TC_OK};

    int a = 15;
    int b = 0;

    tc_assert(divide(a, b) == EINVAL, "Dividing %d by %d should be caught",
              a, b);

    return result;
}

void setup()
{
    debug("This is a setup function");
}

void teardown()
{
    debug("This is a teardown function");
}

int main(void)
{
    Test("test_add", test_add, NULL, NULL);
    Test("test_add_fail", test_add_fail, NULL, NULL);
    Test("test_divide_zero", test_divide_zero, setup, teardown);

    return tc_tests_passed != tc_tests_run;
}
