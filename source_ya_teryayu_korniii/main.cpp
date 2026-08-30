
/*!
    \file
    \brief Main file
    call testfunc.cpp and plot.cpp
*/
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"
#include "testfunc.h"
#include "plot.h"

#define COLOR_CHOOSE "\033[%d;3%dm"

enum roots_flags solve_linear_eq(double b, double c, double* x1, double* x2);
enum roots_flags solve_square_eq(double a, double b, double c, double* x1, double* x2);
int read_coeffs(double* a, double* b, double* c);
int greet_user(void);
int get_sign(double number);
void print_solutions(int count_ans, double* x1, double* x2, int font, int color);
void ask_color(int* font, int* color);
void error_monitor(void);

/**
    Принимает аргументы <имя_файла.txt> и режим тестирования (auto / manual)
    \param argv[] аргументы командной строки <имя_файла.txt> и режим тестирования (auto / manual)
 */
int main(int argc, char* argv[]) { //TODO errno where it possible
    assert(argv);

    double a = NAN, b = NAN, c = NAN;
    int font = 0, color = 0;

    while (greet_user()) {

        if (read_coeffs(&a, &b, &c)) {
            double x1 = NAN, x2 = NAN;
            int count_ans = ERROR_CONST;

            count_ans = solve_equation(a, b, c, &x1, &x2);

            ask_color(&font, &color);
            print_solutions(count_ans, &x1, &x2, font, color);
            draw_function(a, b, c, color);
        }
    }
    printf("Testing process...\n");

    char* name_file = NULL;
    char* test_mode = NULL;

    if (argc == 2) {//NOTE input name file references.txt and test_mode auto or manual
        name_file = argv[1];
        test_mode = argv[2];
    }

    assert(!strcmp(test_mode, "auto") || !strcmp(test_mode, "manual"));
    int right_tests = run_all_tests(name_file, test_mode);
    printf("Right tests: %d\n", right_tests);

    return 0;
}

/**
    Функция приветствия пользователя, спрашивает хочет ли пользователь решить квадратное уравнение и проверяет ввод на корректность.
    В случае некорректного ввода выводит сообщение об этом и просит ввести ответ на вопрос повторно.

    \return 0 значение пропуска решения квадратного уравнения и перехода к тестированию
    \return 1 значение вызова функции решения квадратного уравнения
 */
int greet_user(void) {
    printf("Hello, world!/n"
        "It is AI square solver :)\n"
        "Do you want to solve a quadratic equation?(yes/no)\n");

    const int ANSWER_SIZE_CONST = 8;
    char greetanswer[ANSWER_SIZE_CONST] = "";

    scanf("%5s", greetanswer);  // NOTE: '5' is `ANSWER_SIZE_CONST`-1
    error_monitor();

    if (strcmp("yes", greetanswer) == 0)
        return 1;
    if (strcmp("no", greetanswer) == 0)
        return 0;

    printf("Wrong input! Try again\n");
    return greet_user();
}
/**
    Функция считывающая коэффициенты квадратного уравнения. Проверяет что ввели цифры.

    \param [in] a Указатель на переменную типа double, старший коэффициент
    \param [in] b Указатель на переменную типа double, средний коэффициент квадратного уравнения
    \param [in] c Указатель на переменную типа double, свободный член квадратного уравнения
    \return 0 введено неверное значение
    \return 1 введены корректные коэффициенты
 */
int read_coeffs(double* a, double* b, double* c) {
    assert(a);
    assert(b);
    assert(c);

    printf("Enter the coefficients of the quadratic equation.\n");
    printf("ax^2+bx+c=0\n");
    printf("a b c\n");

    scanf("%lf %lf %lf", a, b, c);

    char buf = 0;///< буфер для проверки корректности ввода

    if ((buf = (char) getchar()) != '\n') {
        if (isalpha(buf))
            printf("ERROR: You wrote letter\n");
        else
            printf("ERROR: wtf !!?!;!!\n");
        return 0;
    }

    return 1;
}
//NOTE - documentation try

/**
    Функция проверяет чему равен старший коэффициент уравнения.
    Если старший коэффициент не является 0 вызывается функция для решения квадратного уравнения,
    иначе функция для решения линейного уравнения.
    \param [in] a Старший коэффициент уравнения
    \param [in] b Средний коэффициент уравнения
    \param [in] c Свободный член
    \param [in] x1 Меньший корень уравнения
    \param [in] x2 Больший корень уравнения
    \return enum roots_flag результат работы функции solve_linear_eq() или solve_square_eq()
 */
enum roots_flags solve_equation(double a, double b, double c, double* x1, double* x2) {
    assert(x2);
    assert(x1);

    if (get_sign(a) == 0)
        return solve_linear_eq(b, c, x1, x2);
    else
        return solve_square_eq(a, b, c, x1, x2);
}

/**
    Функция решения линейного уравнения
    \param b Коэффициент при x
    \param c Свободный член
    \param x1 Корень уравнения
    \param x2 Корень уравнения, совпадает с x1
    \return enum roots_flags константу перечисления количество корней (в том числе бесконечное количество корней или 0 корней)
 */
enum roots_flags solve_linear_eq(double b, double c, double* x1, double* x2) {
    assert(x2);
    assert(x1);
    if (get_sign(b) == 0) {
        if (get_sign(c) == 0)
            return INFINITY_ROOTS;
        else
            return ZERO_ROOTS;
    }
    else {
        *x1 = *x2 = (-c)/b;
        return ONE_ROOT;
    }
}

/**
    Функция решения линейного уравнения
    \param a Старший коэффициент уравнения
    \param b Средний коэффициент уравнения
    \param c Свободный член
    \param x1 Меньший корень уравнения
    \param x2 Больший корень уравнения
    \return enum roots_flags константу перечисления количество корней (в том числе бесконечное количество корней или 0 корней)
 */
enum roots_flags solve_square_eq(double a, double b, double c, double* x1, double* x2) {

    assert(x2);
    assert(x1);
    assert(get_sign(a) != 0);

    double d = b*b - 4*a*c;

    if (get_sign(d) == -1)
        return ZERO_ROOTS;
    else if (get_sign(d) == 0) {
        *x1 = *x2 = (-b) / (2*a);
        return ONE_ROOT;
    }
    else {
        *x1 = ((-b) + sqrt(d)) / (2*a);
        *x2 = ((-b) - sqrt(d)) / (2*a);
        return TWO_ROOT;
    }

    return ERROR_CONST;
}

/**
    \param [in] count_ans Количество корней
    \param [in] x1 Меньший корень
    \param [in] x2 Больший корень
    \param [in] font Цифра, обозначающая шрифт печатаемого текста. Чтобы узнать какой шрифт обозначает цифра см. функцию ask_color()
    \param [in] color Цифра, обозначающая цвет печатаемого текста. Чтобы узнать какой цвет обозначает цифра см. функцию ask_color()
 */
void print_solutions(int count_ans, double* x1, double* x2, int font, int color) {
    assert(x2);
    assert(x1);

    switch (count_ans) {
    case ONE_ROOT:
        printf("One root\n");
        printf(COLOR_CHOOSE "%lg" RESET "\n", font, color, *x1); //NOTE цветной вывод
        break;
    case TWO_ROOT:
        printf("Two roots\n");
        printf(COLOR_CHOOSE "%lg, %lg" RESET "\n", font, color, *x1, *x2); //NOTE цветной вывод
        break;
    case ZERO_ROOTS:
        printf(COLOR_CHOOSE "No roots" RESET "\n", font, color); //NOTE цветной вывод
        break;
    case INFINITY_ROOTS:
        printf(COLOR_CHOOSE "ERROR: an infinite number of roots" RESET "\n", font, color); //NOTE цветной вывод
        break;
    default:
        printf(COLOR_CHOOSE "ERROR: roots didnt read" RESET "\n", font, color); //NOTE цветной вывод
        break;
    }
}

/**
    Функция определяющая знак или равенство 0 числа с плавающей точкой, с заданной точностью
    \param [in] number
    \return 1 Положительное число
    \return 0 Число равно нулю
    \return -1 Отрицательное число
 */
int get_sign(double number) {
    const double EPSILON_5_CONST = 1e-5;

    if (-EPSILON_5_CONST < number && number < EPSILON_5_CONST)
        return 0;
    else if (number < -EPSILON_5_CONST)
        return -1;
    else if (number > EPSILON_5_CONST)
        return 1;

    assert(0 && "Wrong get_sign, take lower const\n");
}
/**
    Функция спрашивающая у пользователя шрифт и цвет для выводимого текста.
    \param [in] font Цифра, обозначающая шрифт печатаемого текста.
    \param [in] color Цифра, обозначающая цвет печатаемого текста.
 */
void ask_color(int* font, int* color) {
    assert(font);
    assert(color);

    printf("What is your favorite font(shrift)?\n");
    printf("0 - reset\n1 - bold text\n4 - emphasized(podch))\n7 - inversion\n");
    scanf("%d", font);
    error_monitor();

    printf("What is your favorite color?\n");
    printf("0 - black\t1 - red \t2 - green\n3 - yellow\t4 - blue\t5 - purple\n6 - light blue\t7 - white.\n");

    scanf("%d", color);
    error_monitor();
}

void error_monitor(void) {
    if (errno)
        perror("Failed: ");
}
