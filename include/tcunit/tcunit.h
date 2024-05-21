#ifndef tcunit_h
#define tcunit_h

#include <stdio.h>

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
} tc_result_code;

/*
 * Unit test result container.
 *
 * code: the tc_result_code.
 * message: the message to print, if any.
 */
typedef struct result {
    tc_result_code code;
    char message[TC_MESSAGE_BUFSIZE];
} tc_Result;



/* ################################ Globals ################################# */

/* Total tests run */
extern int tc_tests_run;
/* Total tests passed */
extern int tc_tests_passed;
/* Total tests failed */
extern int tc_tests_failed;


/* ################################ Functions ############################### */

/*
 * Helper macro for creating asserts.
 *
 * Parameters:
 * test: the condition to test.
 * res: a tc_Result struct holding the test result.
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
#define __tc_assert(test, res, fmt, ...) {    \
        if (!(test)) {\
            res.code = TC_FAIL;\
            snprintf(res.message, TC_MESSAGE_MAX, fmt, ##__VA_ARGS__);\
        }\
        return res;\
    }

/*
 * Macro for asserts.
 *
 * Parameters:
 * test: the condition to test.
 * fmt: the printf-style format string to print if the test fails.
 * ...: the arguments to fmt.
 */
#define tc_assert(test, fmt, ...) {\
        __tc_assert(test, result, fmt, ##__VA_ARGS__);\
    }

/*
 * A tcunit test case.
 *
 * name: the name of the test.
 * f: the address of the test function.
 * setup: a pointer to the test case's setup function.  May be NULL.
 * teardown: a pointer to the test case's teardown function.  May be NULL.
 */
tc_result_code Test(char *name, tc_Result (*f)(void), tc_setup setup, tc_teardown teardown);

#endif
