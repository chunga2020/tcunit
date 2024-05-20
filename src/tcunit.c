#include <tcunit/tcunit.h>

int tc_tests_run = 0;
int tc_tests_passed = 0;
int tc_tests_failed = 0;


tc_result_code Test(char *name, tc_Result (*f)(void), tc_setup setup, tc_teardown teardown) {
    if (setup != NULL) {
        setup();
    }
    fprintf(stderr, "Running test %s:", (name));
    tc_Result result = (f)();
    tc_tests_run++;
    if (teardown != NULL) {
        teardown();
    }

    tc_result_code rc = result.code;

    if (rc == TC_FAIL) {
        fprintf(stderr, "\nFAIL: %s: %s\n", name, result.message);
        tc_tests_failed++;
    } else {
        fprintf(stderr, " PASS\n");
        tc_tests_passed++;
    }

    return rc;
}
