#ifndef MAIN_H
#define MAIN_H

enum rootsflags {
    ERROR_CONST = 8,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOT = 2,
    INFINITY_ROOTS = 3
};

#define RED     "\033[4;31m"
#define GREEN   "\033[4;32m"
#define RESET   "\033[0;0m"
#define ITERATIONS  9

int solve_equation(double a, double b, double c, double* x1, double* x2);

#endif
