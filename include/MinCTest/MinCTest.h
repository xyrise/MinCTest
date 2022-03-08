/* MinCTest.h */
#ifndef MINCTEST_MINCTEST_H
#define MINCTEST_MINCTEST_H

#include <stddef.h>
#include <stdlib.h>


typedef struct TestGroup {
  char **test_names;
  int (**tests)(void);
  size_t num_tests;
} TestGroup;

#define registerTest(testgroup, test) \
  if (!testgroup.num_tests) { \
    testgroup.test_names = malloc(sizeof(char *)); \
    testgroup.tests = malloc(sizeof(int (*)(void))); \
  } \
  else { \
    testgroup.test_names = realloc( \
        testgroup.test_names, \
        (testgroup.num_tests + 1) * sizeof(char *) \
    ); \
    testgroup.tests = realloc( \
        testgroup.tests, \
        (testgroup.num_tests + 1) * sizeof(int (*)(void)) \
    ); \
  } \
  testgroup.test_names[testgroup.num_tests] = #test; \
  testgroup.tests[testgroup.num_tests] = &test; \
  testgroup.num_tests++;


int runTest(TestGroup const *const, char const *const);
int runTests(TestGroup const *const);


#endif /* MINCTEST_MINCTEST_H */
