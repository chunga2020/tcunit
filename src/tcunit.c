#include <stdio.h>
#include <stdlib.h>
#include <tcunit/tcunit.h>

int tc_tests_run = 0;
int tc_tests_passed = 0;
int tc_tests_failed = 0;

void tc_start()
{
    message = malloc(TC_MESSAGE_BUFSIZE);
}

void tc_finish()
{
    free(message);
}

tc_result Test(char *name, tc_result (*f)(void), tc_setup setup, tc_teardown teardown) {
    fprintf(stderr, "Running test %s:\n", (name));
    if (setup != NULL) {
        setup();
    }
    tc_result rc = f();
    tc_tests_run++;
    if (teardown != NULL) {
        teardown();
    }

    if (rc == TC_FAIL) {
        fprintf(stderr, "FAIL: %s: %s\n", name, message);
        tc_tests_failed++;
    } else {
        fprintf(stderr, "PASS\n");
        tc_tests_passed++;
    }

    return rc;
}

int tc_report(char *name)
{
    fprintf(stderr,
            "---- Summary: %s ----\n"
            "Tests run: %d\tPasses: %d\tFailures: %d\n", name, tc_tests_run,
            tc_tests_passed, tc_tests_failed);

    if (tc_tests_passed == tc_tests_run) {
        fprintf(stderr, "ALL TESTS PASSED\n");
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
