#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "plot.h"
#include "testfunc.h"
#include "main.h"

int solve_linear_eq(double b, double c, double* x1, double* x2);
int solve_square_eq(double a, double b, double c, double* x1, double* x2);
int read_coeffs(double* a, double* b, double* c);
int greet_user();
int get_sign(double number);
void print_solutions(int count_ans, double* x1, double* x2, int* font, int* color);
void get_color(int* font, int* color);

int main() {
    double a = NAN, b = NAN, c = NAN;
    int font = 0, color = 0;

    while (greet_user()) {


        if (read_coeffs(&a, &b, &c)) {
            double x1 = NAN, x2 = NAN;
            int count_ans = ERROR_CONST;

            count_ans = solve_equation(a, b, c, &x1, &x2);

            print_solutions(count_ans, &x1, &x2, &font, &color);
            draw_function(a, b, c, color);
        }
    }
    int run_all_tests(void);
    printf("Right tests: %d\n", run_all_tests());

    return 0;
}

int greet_user() {
    printf("Hello, world! Do you want to solve a quadratic equation?(yes/no)\n");

    const int ANSWER_SIZE_CONST = 6;
    char greetanswer[ANSWER_SIZE_CONST] = "";
    const char* RIGHT_ANSWER_CONST = "yes";
    const char* WRONG_ANSWER_CONST = "no";

    scanf("%5s", greetanswer);  // NOTE: '5' is `ANSWER_SIZE_CONST`-1

    if (strcmp(RIGHT_ANSWER_CONST, greetanswer) == 0)
        return 1;
    else if (strcmp(WRONG_ANSWER_CONST, greetanswer) == 0)
        return 0;
    else {
        printf("Wrong input, try again\n");
        return greet_user();
    }

    return 0;
}

int read_coeffs(double* a, double* b, double* c) {
    assert(a != NULL && "ERROR: wrong a");
    assert(b != NULL && "ERROR: wrong b");
    assert(c != NULL && "ERROR: wrong c");

    printf("Enter the coefficients of the quadratic equation.\n");
    printf("ax^2+bx+c=0\n");

    scanf("%lf %lf %lf", a, b, c);
    char buf = 0;

    if ((buf = (char) getchar()) != '\n') {
        if (isalpha(buf))
            printf("ERROR: You wrote letter\n");
        else
            printf("ERROR: wtf !!?!;!!\n");
        return 0;
    }

    return 1;
}

int solve_equation(double a, double b, double c, double* x1, double* x2) {
    assert(x2 != NULL && "ERROR: wrong x2");
    assert(x1 != NULL && "ERROR: wrong x1");
    if (get_sign(a) == 0) {
        if (get_sign(b) == 0) {
            if (get_sign(c) == 0)
                return INFINITY_ROOTS;
            else
                return ZERO_ROOTS;
        }
        else
            return solve_linear_eq(b, c, x1, x2);
    }
    else
        return solve_square_eq(a, b, c, x1, x2);
}

int solve_linear_eq(double b, double c, double* x1, double* x2) {
    assert(x2 != NULL && "ERROR: wrong x2");
    assert(x1 != NULL && "ERROR: wrong x1");
    assert(get_sign(b) != 0);

    *x1 = *x2 = (-c)/b;

    return ONE_ROOT;
}

int solve_square_eq(double a, double b, double c, double* x1, double* x2) {
    assert(x2 != NULL && "ERROR: wrong x2");
    assert(x1 != NULL && "ERROR: wrong x1");
    assert(get_sign(a) != 0);

    double d = b*b - 4*a*c;

    if (get_sign(d) == -1)
        return ZERO_ROOTS;
    else if (get_sign(d) == 0) {
        *x1 = *x2 = (-b) / (2 * a);
        return ONE_ROOT;
    }
    else {
        *x1 = ((-b) + sqrt(d)) / (2 * a);
        *x2 = ((-b) - sqrt(d)) / (2 * a);
        return TWO_ROOT;
    }

    return ERROR_CONST;
}

void print_solutions(int count_ans, double* x1, double* x2, int* font, int* color) {
    assert(x2 != NULL && "ERROR: wrong x2");
    assert(x1 != NULL && "ERROR: wrong x1");

    get_color(font, color);
    switch (count_ans){
    case 1:
        printf("One root\n");
        printf("\033[%d;3%dm" "%4.f  \033[0m\n", *font, *color, *x1);
        break;
    case 2:
        printf("Two roots\n");
        printf("\033[%d;3%dm %4.2f, %6.2f \033[0m\n", *font, *color, *x1, *x2);
        break;
    case 0:
        printf("\033[%d;3%dm No roots \033[0m\n", *font, *color);
        break;
    case 3:
        printf("\033[%d;3%dm ERROR: an infinite number of roots \033[0\n", *font, *color);
        break;
    default:
        printf("\033[%d;3%dm ERROR: roots didnt read \033[0m\n", *font, *color);
        break;
    }
}

int get_sign(double number) {
    const double EPSILON_4_CONST = 0.00001; // TODO: 1e-5

    if (-EPSILON_4_CONST < number && number < EPSILON_4_CONST)
        return 0;
    else if (number < -EPSILON_4_CONST)
        return -1;
    else if (number > EPSILON_4_CONST)
        return 1;
    else {
        printf("Wrong get_sign, take lower const\n");
        return 0;
    }
}

void get_color(int* font, int* color) {
    assert(font != NULL && "ERROR: wrong font");
    assert(color != NULL && "ERROR: wrong color");

    printf("What is your favourite font(shrift)?\n");
    printf("0 - reset\n1 - bold text\n4 - emphasized(podch))\n7 - invers\n");
    scanf("%d", font);

    printf("What is your favourite get_color?\n");
    printf("0 - black\t1 - red \t2 - green\n3 - yellow\t4 - blue\t5 - purple\n6 - light blue\t7 - white.\n");

    scanf("%d", color);
}
