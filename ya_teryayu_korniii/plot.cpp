#include "plot.h"

int calc_function(double a, double b, double c, int x);

int calc_function(double a, double b, double c, int x) {
    return round(a*x*x + b*x + c);
}

int draw_function(double a, double b, double c, int color) {
    const int WIDTH_CONST = 35;
    const int HEIGHT_CONST = 20;
    int x = 0, line = 0, flag_drawn = 0;
    int y = calc_function(a, b, c, -WIDTH_CONST);

    for(line = HEIGHT_CONST; line > -HEIGHT_CONST; line--){
        for (x = -WIDTH_CONST; x < WIDTH_CONST; x++){
            y = calc_function(a, b, c, x);
            if (y != line) {
                if (x == 0 && line == 0)
                    printf("\033[;3%dm+\033[0;0m", color);
                else if (x == 0)
                    printf("\033[;3%dm|\033[0;0m", color);
                else if (line == 0)
                    printf((x == WIDTH_CONST-1) ? "\n" : "\033[;3%dm—\033[0;0m", color);
                else
                    printf((x == WIDTH_CONST-1) ? "\n" : " ");
            }
            else{
                printf("\033[;3%dm*\033[0;0m", color);
                flag_drawn = 1;
            }
        }
    }
    if (!flag_drawn){
        printf("Лох, график вне поля консоли");
    }
    return RIGHT_EXIT;
}
