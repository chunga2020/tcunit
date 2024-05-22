# tcunit: A Tiny C Unit Testing Framework

## Building

To build `tcunit`, simply type

``` bash
make
make install
```

This will build the library, run the tests, and install the library.  By
default, the install location is `$PREFIX/include` for the header and
`$PREFIX/lib` for the library, with `$PREFIX` defaulting to `/usr/local/`.

## Usage

To use `tcunit`, `#include <tcunit/tcunit.h>` in your test source.  `tcunit`
supports defining optional setup and teardown fixtures, with the following
signatures:

``` c
void setup(void);
void teardown(void);
```

To create a test, define a test function with a signature similar to

``` c
tc_result test_foo(void);
```

These test functions should end with `return TC_OK`, which signals success.


In the tests, use the `tc_assert(test, fmt, ...);` macro to do the actual
checks. `test` is the condition to check, and `fmt` and `...` are arguments to a
typical `printf(3)`-style string.  This macro automatically handles returning a
failure, marked with the macro `TC_FAIL`, if `test` evaluates to 0 or `false`.

Finally, define a test wrapper that looks like:

``` c
void all_tests()
{
    Test("test_name1", test_func, your_setup_func, your_teardown_func);
    Test("test_name2", another_test_func, your_setup_func, your_teardown_func);
    // ...
}
```

that contains all of your tests.

The signature of `Test` is
```c
tc_result Test(char *name, tc_result(*f)(void), tc_setup setup, tc_teardown teardown);
```

where

* `name` is the name of the test
* `f` is the test function mentioned earlier
* `setup` is a pointer to your setup fixture, or `NULL`
* `teardown` is a pointer to your teardown fixture, or `NULL`

Pass this wrapper into the `TC_RUN_TESTS` macro, which will take care of setup
and teardown of the entire test module.
