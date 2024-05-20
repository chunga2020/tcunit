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
 * A tcunit test case.
 *
 * name: the name of the test.
 * f: the address of the test function.
 * setup: a pointer to the test case's setup function.  May be NULL.
 * teardown: a pointer to the test case's teardown function.  May be NULL.
 */
tc_result_code Test(char *name, tc_Result (*f)(void), tc_setup setup, tc_teardown teardown);

#endif
