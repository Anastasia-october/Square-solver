/**
    \file
    \brief Release drawing plot in terminal
    \details  График привязан к точке пересечения осей, оси координат рисуются белым цветом,
    график - цветом, выбранным пользователем.
 */
#include "plot.h"

#define COLOR_CHOOSE "\033[%d;3%dm"

int calc_function(double a, double b, double c, int x);
void print_symbol(int x, int right_line, int line, const int WIDTH_CONST, int* flag_drawn, int color);

/**
    Функция вычисляющая и округляющая по правилам математики значение квадратичной функции
    \param [in] a Старший коэффициент уравнения
    \param [in] b Средний коэффициент уравнения
    \param [in] c Свободный член
    \param [in] x координата по оси абсцисс
 */
int calc_function(double a, double b, double c, int x) {
    if ((a*x*x + b*x + c) > 32000.0)
        return INT_MAX;
    else
        return (int) round(a*x*x + b*x + c);
}

/**
    Функция печати графика функции в консоли.
    \param [in] a Старший коэффициент уравнения
    \param [in] b Средний коэффициент уравнения
    \param [in] c Свободный член
    \param [in] color Цифра, обозначающая цвет графика
 */
void draw_function(double a, double b, double c, int color) {
    const int WIDTH_CONST = 35;
    const int HEIGHT_CONST = 20;
    int x = 0, line = 0, flag_drawn = 0, y = 0;

    for(line = HEIGHT_CONST; line > -HEIGHT_CONST; line--) {
        for (x = -WIDTH_CONST; x <= WIDTH_CONST; x++) {
            y = calc_function(a, b, c, x);
            if y != line
                int right_line = 1;
            else
                int right_line = 0;
            print_symbol(x, right_line, line, WIDTH_CONST, &flag_drawn, color);
        }
    }

    if (!flag_drawn) {
        printf("Лох, график вне поля консоли");
    }
}

/**
    Функция печатающая символ в зависимости от положения курсора в консоли
    \param [in] x Положение курсора по оси абсцисс
    \param [in] right_line Показывает находится ли точка функции на текущей строке
    \param [in] line Номер строки
    \param [in] WIDTH_CONST Константа - ширина консоли
    \param [in] flag_drawn Флаг показывающий был ли нарисован хотя бы один символ графика
    \param [in] color Цифра, обозначающая цвет графика
 */
void print_symbol(int x, int right_line, int line, const int WIDTH_CONST, int* flag_drawn, int color) {
    assert(flag_drawn != NULL && "ERROR wrong flag_drawn");

    if (right_line) {
        if (x == 0 && line == 0)
            printf(WHITE "+" RESET);
        else if (x == 0)
            printf(WHITE "|" RESET);
        else if (line == 0)
            printf((x == WIDTH_CONST) ? "\n" : WHITE "—" RESET);
        else
            printf((x == WIDTH_CONST) ? "\n" : " ");
    }
    else {
        printf(COLOR_CHOOSE "*" RESET, color);
        *flag_drawn = 1;
    }
}
