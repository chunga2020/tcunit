#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tcunit/tcunit.h>
#include <tcunit/dbg.h>

#define MAXNAME 32

typedef struct Person {
    char *name;
    int age;
    int height;
    int weight;
} Person;

Person *person_create()
{
    Person *p = calloc(1, sizeof(Person));

    return p;
}

int person_init(Person *p, char *name, int age, int height, int weight)
{
    check(p != NULL, "NULL Person pointer");

    p->name = strndup(name, MAXNAME - 1);
    p->age = age;
    p->height = height;
    p->weight = weight;

    return 0;
 error:
    return -1;
}

void person_destroy(Person **p)
{
    if (*p != NULL) {
        if ((*p)->name != NULL) {
            free((*p)->name);
        }
        free(*p);
    }
}

/* ###### Test values ##### */

Person *p;
char *the_name = "Joe Schmoe";
int age = 25;
int height = 68; /* inches */
int weight = 165; /* pounds */

/* Test boilerplate stuff */

void setup()
{
    debug("Making a person");
    p = person_create();
    (void)person_init(p, the_name, age, height, weight);
}

void teardown()
{
    debug("Cleaning up the person");
    person_destroy(&p);
    p = NULL;
}

/* The tests */

tc_result test_create()
{
    tc_assert((p = person_create()) != NULL, "Failed to create a person");

    return TC_OK;
}

tc_result test_init()
{
    tc_assert(strncmp(p->name, the_name, MAXNAME) == 0,
              "Expected name to be %s but was %s", the_name, p->name);
    tc_assert(p->age == age,
              "Expected %s's age to be %d but it was %d", p->name, age, p->age);
    tc_assert(p->height == height,
              "Expected his height to be %d but it was %d", p->height, height);
    tc_assert(p->weight == weight,
              "Expected his weight to be %d but it was %d", p->weight, weight);

    return TC_OK;
}

tc_result test_type_eq()
{
    int x = 6;
    int y = x * 2;
    tc_assert_int_eq(12, y, "x", "y");

    char *s1 = "Hello, world!";
    char *s2 = "Hello, world!";
    tc_assert_str_eq(s1, s2, "s1", "s2", MAXNAME);

    bool b1 = true;
    bool b2 = true;
    tc_assert_bool_eq(b1, b2, "b1", "b2");

    return TC_OK;
}

void all_tests()
{
    Test("test_create", test_create, NULL, teardown);
    Test("test_init", test_init, setup, teardown);
    Test("type assert macros", test_type_eq, NULL, NULL);
}

TC_RUN_TESTS(all_tests)
