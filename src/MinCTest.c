/* MinCTest.c */
#include "MinCTest.h"

#include <string.h>


int runTest(TestGroup const *const tg, char const *const test_name) {
  size_t i;
  for (i = 0; i < tg->num_tests; ++i) {
    if (!strcmp(tg->test_names[i], test_name)) {
      return (*(tg->tests[i]))();
    }
  }
  return 1;
}

int runTests(TestGroup const *const tg) {
  int num_errors = 0;
  size_t i;
  for (i = 0; i < tg->num_tests; ++i) {
    if (!((*(tg->tests[i]))())) num_errors++;
  }
  return num_errors;
}
