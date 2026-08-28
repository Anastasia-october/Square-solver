#ifndef TESTFUNC_H
#define TESTFUNC_H

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "colors.h"

struct TestCase
{
    double a, b, c;
    int number_of_roots_ref;
    double x1Ref, x2Ref;
};

int run_all_tests(char* name_file, char* test_mode);

#endif
