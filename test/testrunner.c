/* testrunner.c */

#include "MinCTest/MinCTest.h"

#include "basic/empties.c"
#include "basic/empties2.c"


int main(int argc, char *argv[]) {
  TestRunner tr = newTestRunner();

  registerTestGroup(tr, "basic");
  registerTest(tr, "basic", empties);
  registerTest(tr, "basic", empties2);

  return runTests(tr, argc, argv);
}
