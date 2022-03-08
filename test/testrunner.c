/* testrunner.c */

#include "MinCTest/MinCTest.h"

#include "basic/empties.c"
#include "basic/empties2.c"


int main(int argc, char *argv[]) {
  TestGroup basic = {0};

  registerTest(basic, empties);
  registerTest(basic, empties2);

  if (argc < 2) {
    return runTests(&basic);
  }
  else if (argc == 2) {
    return runTest(&basic, argv[1]);
  }
  return 1;
}
