#ifndef MAIN_H
#define MAIN_H

enum roots_flags {
    ERROR_CONST = 8,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOT = 2,
    INFINITY_ROOTS = 3
};

enum color_args {
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    purple = 5,
    light_blue = 6,
    white = 7
};

enum font_args {
    reset = 0,
    bold_text = 1,
    emphasized_podch = 4,
    inversion = 7
};

#include "colors.h"

enum roots_flags solve_equation(double a, double b, double c, double* x1, double* x2);

#endif
