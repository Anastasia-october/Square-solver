#ifndef TESTFUNC_H
#define TESTFUNC_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define ITERATIONS 8

#define RED     "\033[4;31m"
#define GREEN "\033[4;32m"
#define RESET "\033[0;0m"

struct TestCase
{
    double a, b, c;
    int nRootsRef;
    double x1Ref, x2Ref;
};

int run_all_tests(void);

#endif
