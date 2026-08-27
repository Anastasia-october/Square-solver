#ifndef TESTFUNC_H
#define TESTFUNC_H
//MENTOR нужно ли переносить include-ы в сишник
//MENTOR нужно ли убрать #include <assert.h> из testfunc или из main
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define ITERATIONS 9
#define RANGE_LENGTH 100
#define RANGE_MAXIMUM 50
//#define frand() ((double) rand() / (RAND_MAX+1.0))

#define RED   "\033[4;31m"
#define GREEN "\033[4;32m"
#define RESET "\033[0;0m"

struct TestCase
{
    double a, b, c;
    int number_of_roots_ref;
    double x1Ref, x2Ref;
};

int run_all_tests(void);

#endif
