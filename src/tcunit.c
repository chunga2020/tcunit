#include <tcunit/tcunit.h>

int tc_tests_run = 0;
int tc_tests_passed = 0;
int tc_tests_failed = 0;


tc_result_code Test(char *name, tc_Result (*f)(void), tc_setup setup, tc_teardown teardown) {
    fprintf(stderr, "Running test %s:\n", (name));
    if (setup != NULL) {
        setup();
    }
    tc_Result result = f();
    tc_tests_run++;
    if (teardown != NULL) {
        teardown();
    }

    tc_result_code rc = result.code;

    if (rc == TC_FAIL) {
        fprintf(stderr, "FAIL: %s: %s\n", name, result.message);
        tc_tests_failed++;
    } else {
        fprintf(stderr, "PASS\n");
        tc_tests_passed++;
    }

    return rc;
}
