#ifndef MAIN_H
#define MAIN_H

/// \brief Набор возможных количеств корней
enum roots_flags {
    ERROR_CONST = 8, /// < число лдя обозначения ошибки, устанавливается при инициализации переменной и возвращается в случае не изменения корней
    ZERO_ROOTS = 0, /// < ноль кореей
    ONE_ROOT = 1, /// < один корень
    TWO_ROOT = 2, /// < два корня
    INFINITY_ROOTS = 3 /// < бесконечное количество корней
};

#include "colors.h"

enum roots_flags solve_equation(double a, double b, double c, double* x1, double* x2);

#endif
