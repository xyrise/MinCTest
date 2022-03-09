/* MinCTest.h */
#ifndef MINCTEST_MINCTEST_H
#define MINCTEST_MINCTEST_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


typedef int (*Test)(void);

typedef struct TestGroup {
  char const **test_names;
  Test *tests;
  size_t num_tests;
} *TestGroup;

typedef struct TestRunner {
  char const **group_names;
  TestGroup *groups;
  size_t num_groups;
} *TestRunner;

TestRunner newTestRunner() { return calloc(1, sizeof(struct TestRunner)); }
void deleteTestRunner(TestRunner tr) { free(tr); }

Test getTest(TestRunner const, char const *const, char const *const);
void setTest(TestRunner, char const *const, char const *const, Test const);
void registerNamedTest(
    TestRunner,
    char const *const,
    char const *const,
    Test const
);
#define registerTest(tr, group, t) \
  registerNamedTest(tr, group,  #t, t)

TestGroup getTestGroup(TestRunner, char const *const);
void setTestGroup(TestRunner, char const *const, TestGroup const);
void registerTestGroup(TestRunner, char const *const);

int runTest(TestRunner const, char const *const, char const *const);
int runTestGroup(TestRunner const, char const *const);
int runTestsOffset(
    TestRunner const,
    int const,
    char **,
    int const
);
int runTests(TestRunner const, int const, char **);


Test getTest(
    TestRunner const tr,
    char const *const group,
    char const *const test
) {
  size_t i;
  size_t j;
  if (!tr || !group || !test) return NULL;

  for (i = 0; i < tr->num_groups; ++i)
    if (!strcmp(tr->group_names[i], group))
      for (j = 0; j < tr->groups[i]->num_tests; ++j)
        if (!strcmp(tr->groups[i]->test_names[j], test))
          return tr->groups[i]->tests[j];

  return NULL;
}

void setTest(
    TestRunner tr,
    char const *const group,
    char const *const test,
    Test const t
) {
  size_t i;
  TestGroup tg;
  if (!tr || !group || !test || !t) return;

  tg = getTestGroup(tr, group);
  if (!tg) return;

  for (i = 0; i < tg->num_tests; ++i) {
    if (!strcmp(tg->test_names[i], test)) {
      tg->tests[i] = t;
      return;
    }
  }

  if (tg->num_tests) {
    tg->test_names = realloc(
        tg->test_names,
        (tg->num_tests + 1) * sizeof(char *)
    );
    tg->tests = realloc(
        tg->tests,
        (tg->num_tests + 1) * sizeof(Test)
    );
  }
  else {
    tg->test_names = malloc(sizeof(char *));
    tg->tests = malloc(sizeof(Test));
  }
  tg->test_names[tg->num_tests] = test;
  tg->tests[tg->num_tests] = t;
  tg->num_tests++;
}

void registerNamedTest(
    TestRunner tr,
    char const *const group,
    char const *const test,
    Test const t
) {
  if (!tr || !group || !test || getTest(tr, group, test)) return;
  setTest(tr, group, test, t);
}

TestGroup getTestGroup(TestRunner tr, char const *const group) {
  size_t i;
  if (!tr || !group) return NULL;

  for (i = 0; i < tr->num_groups; ++i)
    if (!strcmp(tr->group_names[i], group))
      return tr->groups[i];

  return NULL;
}

void setTestGroup(TestRunner tr, char const *const group, TestGroup const tg) {
  size_t i;
  if (!tr || !group || !tg) return;

  for (i = 0; i < tr->num_groups; ++i) {
    if (!strcmp(tr->group_names[i], group)) {
      /* NOTE: This may cause memory leaks if the old TestGroup is not
       * retrieved and freed first. */
      tr->groups[i] = tg;
      return;
    }
  }

  if (tr->num_groups) {
    tr->group_names = realloc(
        tr->group_names,
        (tr->num_groups + 1) * sizeof(char *)
    );
    tr->groups = realloc(
        tr->groups,
        (tr->num_groups + 1) *  sizeof(TestGroup)
    );
  }
  else {
    tr->group_names = malloc(sizeof(char *));
    tr->groups = malloc(sizeof(TestGroup));
  }

  tr->group_names[tr->num_groups] = group;
  tr->groups[tr->num_groups] = tg;
  tr->num_groups++;
}

void registerTestGroup(TestRunner tr, char const *const group) {
  if (!tr || !group || getTestGroup(tr, group)) return;

  if (tr->num_groups) {
    tr->group_names = realloc(
        tr->group_names,
        (tr->num_groups + 1) * sizeof(char *)
    );
    tr->groups = realloc(
        tr->groups,
        (tr->num_groups + 1) *  sizeof(TestGroup)
    );
  }
  else {
    tr->group_names = malloc(sizeof(char *));
    tr->groups = malloc(sizeof(TestGroup));
  }

  tr->group_names[tr->num_groups] = group;
  tr->groups[tr->num_groups] = calloc(1, sizeof(struct TestGroup));
  tr->num_groups++;
}

int runTest(
    TestRunner const tr,
    char const *const group,
    char const *const test
) {
  Test t;
  if (!tr || !group || !test) return -1;

  t = getTest(tr, group, test);
  if (!t) return -1;

  return (*t)();
}

int runTestGroup(TestRunner const tr, char const *const group) {
  size_t i;
  int num_errors = 0;
  TestGroup tg;
  if (!tr || !group) return -1;

  tg = getTestGroup(tr, group);
  if (!tg) return -1;

  for (i = 0; i < tg->num_tests; ++i) {
    if (!((*(tg->tests[i]))())) num_errors++;
  }

  return num_errors;
}

int runTestsOffset(
    TestRunner const tr,
    int const argc,
    char **argv,
    int const arg_offset
) {
  size_t i;
  size_t j;
  int num_errors;
  int ai;
  if (!tr) return -1;

  if (argc < 1 + arg_offset) {
    num_errors = 0;
    for (i = 0; i < tr->num_groups; ++i) {
      for (j = 0; j < tr->groups[i]->num_tests; ++j) {
          if (!((*(tr->groups[i]->tests[j]))())) num_errors++;
      }
    }
    return num_errors;
  }
  else if (argc == 1 + arg_offset) {
    return runTestGroup(tr, argv[arg_offset]);
  }
  else {
    num_errors = 0;
    for (ai = arg_offset + 1; ai < argc; ++ai)
      if (runTest(tr, argv[arg_offset], argv[ai])) num_errors++;
    return num_errors;
  }
}

int runTests(TestRunner const tr, int const argc, char **argv) {
  int result;
  result = runTestsOffset(tr, argc, argv, 1);
  return result;
}


#endif /* MINCTEST_MINCTEST_H */
