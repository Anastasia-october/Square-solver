#include "plot.h"

int calc_function(double a, double b, double c, int x);
void print_symbol(int x, int y, int line, const int WIDTH_CONST, int* flag_drawn, int color);

int calc_function(double a, double b, double c, int x) {
    return (int) lround(a*x*x + b*x + c);
    return INT_MAX;
}

int draw_function(double a, double b, double c, int color) {
    const int WIDTH_CONST = 35;
    const int HEIGHT_CONST = 20;
    int x = 0, line = 0, flag_drawn = 0, y = 0;

    for(line = HEIGHT_CONST; line > -HEIGHT_CONST; line--){
        for (x = -WIDTH_CONST; x <= WIDTH_CONST; x++){
            y = calc_function(a, b, c, x);
            print_symbol(x, y, line, WIDTH_CONST, &flag_drawn, color);
        }
    }
    if (!flag_drawn){
        printf("Лох, график вне поля консоли");
    }
    return RIGHT_EXIT;
}

void print_symbol(int x, int y, int line, const int WIDTH_CONST, int* flag_drawn, int color) {
    assert(flag_drawn != NULL && "ERROR wrong flag_drawn");

    if (y != line) {
        if (x == 0 && line == 0)
            printf(WHITE "+" RESET);
        else if (x == 0)
            printf(WHITE "|" RESET);
        else if (line == 0)
            printf((x == WIDTH_CONST) ? "\n" : WHITE "—" RESET);
        else
            printf((x == WIDTH_CONST) ? "\n" : " ");
    }
    else{
        printf("\033[;3%dm" "*" RESET, color);
        *flag_drawn = 1;
    }
}
