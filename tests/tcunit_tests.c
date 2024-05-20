#include <stdio.h>
#include <tcunit/tcunit.h>

#include <tcunit/tests/math.h>

tc_Result test_add()
{
    tc_Result result = {.code = TC_OK};

    int a = 5;
    int b = 5;
    int expect = 10;
    int actual = add(a, b);

    if (actual != expect) {
        result.code = TC_FAIL;
        snprintf(result.message, TC_MESSAGE_MAX,
                 "Adding %d and %d failed.  Expected: %d.  Actual %d",
                 a, b, expect, actual);
    }

    return result;
}

tc_Result test_add_fail()
{
    tc_Result result = {.code=TC_OK};

    int a = 5;
    int b = 15;
    int expect = 10;
    int actual = add(a, b);

    if (actual != expect) {
        result.code = TC_FAIL;
        snprintf(result.message, TC_MESSAGE_MAX,
                 "Adding %d and %d failed.  Expected: %d.  Actual: %d",
                 a, b, expect, actual);
    }

    return result;
}

int main(void)
{
    Test("test_add", test_add, NULL, NULL);
    Test("test_add_fail", test_add_fail, NULL, NULL);

    return tc_tests_passed != tc_tests_run;
}
