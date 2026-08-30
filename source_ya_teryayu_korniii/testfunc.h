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

/**!
    \brief Структура TestCase
    \details Структура для хранения и использования тестовых данных
 */
struct TestCase
{
    double a, b, c; /** коэффициенты квадратного уравнения */
    int number_of_roots_ref; /** количество корней */
    double x1Ref, x2Ref; /** корни уравнения*/
};

int run_all_tests(char* name_file, char* test_mode);

#endif
