#ifndef tcunit_h
#define tcunit_h

#include <stdio.h>
#include <stdlib.h>

#include <tcunit/dbg.h>

/* SPDX-License-Identifier: MIT */

/* ############################### Constants ################################ */
#define TC_MESSAGE_BUFSIZE 4096
#define TC_MESSAGE_MAX (TC_MESSAGE_BUFSIZE) - 1

/* ############################ Useful typedefs ############################# */

/*
 * A pointer to a setup function that tests run before they execute.
 */
typedef void (*tc_setup)(void);

/*
 * A pointer to a cleanup function that tests run after they execute.
 */
typedef void (*tc_teardown)(void);

/* Return codes for unit tests */
typedef enum {
    TC_FAIL = -1,
    TC_OK = 0
} tc_result;


/* ################################ Globals ################################# */

/* Total tests run */
extern int tc_tests_run;
/* Total tests passed */
extern int tc_tests_passed;
/* Total tests failed */
extern int tc_tests_failed;

extern char *message;


/* ################################ Functions ############################### */

/*
 * Macro for creating asserts.
 *
 * Parameters:
 * test: the condition to test.
 * fmt: the printf-style format string to print.
 * ...: the arguments to fmt.
 *
 * Notes:
 * The maximum length of fmt, after printf construction is TC_MESSAGE_MAX bytes.
 * Truncation will occur if the string is longer than that.
 *
 * The return statement ensures that a failing test bails out immediately, so it
 * is clear precisely what failed.  Cleanup may be achieved by employing a
 * teardown function in the test case.
 */
#define tc_assert(test, fmt, ...) {    \
        if (!(test)) {\
            snprintf(message, TC_MESSAGE_MAX, fmt, ##__VA_ARGS__);\
            return TC_FAIL;\
        }\
    }

/* Sets up the framework. */
void tc_start();

void tc_finish();

/*
 * A tcunit test case.
 *
 * name: the name of the test.
 * f: the address of the test function.
 * setup: a pointer to the test case's setup function.  May be NULL.
 * teardown: a pointer to the test case's teardown function.  May be NULL.
 */
tc_result Test(char *name, tc_result (*f)(void), tc_setup setup, tc_teardown teardown);

/*
 * Print a summary of a test run.
 *
 * Parameters:
 * name: the name of the test run
 *
 * Return:
 * On success, returns EXIT_SUCCESS.  On failure, returns EXIT_FAILURE.
 */
int tc_report(char *name);

/*
 * GCC outputs warnings about 'message' and 'argc' being unused.  These can
 * safely be ignored.  The declaration of message is needed for the test files
 * when the macro is expanded.  We need argc because we need the
 * (int argc, char *argv[]) form of main to get access to the executable name.
 */
#define TC_RUN_TESTS(tests) char *message;\
    int main(int argc, char *argv[]) {                          \
        fprintf(stderr, "----- Running: %s -----\n", argv[0]);\
        debug("%d", argc);\
        tc_start();\
        tests();\
        tc_finish();\
        exit(tc_report(argv[0]));\
    }

#endif
