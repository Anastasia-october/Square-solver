#include <stdio.h>
#include  <math.h>
#include <string.h>
#include <assert.h>

//MENTOR - ERRORCONST = -1

enum rootsflags {
    ERRORCONST = 8,
    ZEROROOTS = 0,
    ONEROOT = 1,
    TWOROOTS = 2,
    INFINITEROOTS = 3};

#define ANSWERSIZE 6
#define EPSIL 0.0000000001 /*маленькое число для сравнений*/
#define RIGHTANS "yes"
#define WRONGANS "no"
#define RED "\033[4;31m"
#define GREEN "\033[4;32m"
#define RESET "\033[0;0m"
#define TOCHNOST 4 // Accuracy
#define ITERATIONS 8

int getanswer(double a, double b, double c, double* x1, double* x2);
int korni_1(double k, double c, double* x1, double* x2);
int korni_2(double a, double b, double c, double* x1, double* x2);
int rightscan(double* a, double* b, double* c); //IsInputCorrect or IsInputValid
void outp(int count_ans, double* x1, double* x2);
void description(void);
int greet();
int comparison(double L);
void color(int* q, int* w);
int number_of_tests(int* number_of_t);
int RunTests(int number_of_tests);


int main()
{
    int iter = greet();
    while (iter){
        description();

        double a = 0.0, b = 0.0, c = 0.0;
        printf("a = %lg, b = %lg, c = %lg\n", a, b, c);

        if (rightscan(&a, &b, &c)){
            double x1 = NAN, x2 = NAN;
            int count_ans = ERRORCONST;

            count_ans = getanswer(a, b, c, &x1, &x2);
            outp(count_ans, &x1, &x2);
        }
        iter = greet();
    }
    int number_of_t = 0;
    number_of_tests(&number_of_t);

    printf("Right tests: %d\n", RunTests(number_of_t));
    return 0;
}



int greet()
{
    printf("Hello, world! Do you want to solve a quadratic equation?(yes/no)\n");

    char greetanswer[ANSWERSIZE] = "";
    scanf("%s", greetanswer);

    /*printf("%s\n", greetanswer);*/ //FIXME -задваивание при неверных абс

    char answer_agree[ANSWERSIZE] = RIGHTANS;
    char answer_disagree[ANSWERSIZE] = WRONGANS;

    if (strcmp(answer_agree, greetanswer) == 0){
        return 1;
    }
    else if (strcmp(answer_disagree, greetanswer) == 0){
            return 0;
    }
    else{
        printf("Wrong input, try again\n");
        return greet();
    }
    return 0;
}



void description(void)
{
    printf("Enter the coefficients of the quadratic equation.\n");
    printf("ax^2+bx+c=0\n");
}



int rightscan(double* a, double* b, double* c)
{
    scanf("%lf %lf %lf", a, b, c);
    char buf = 0;
    if ((buf = (char) getchar()) != '\n'){
        if ((buf >= 'A' && buf <= 'Z') || (buf >= 'a' && buf <= 'z')){
            printf("ERROR: You wrote letter\n");
        }
        else{
            printf("ERROR: wtf !!?№!;!№!\n");
        }
        return 0;
    }
    return 1;
}



int getanswer(double a, double b, double c, double* x1, double* x2)
{
    if (comparison(a) == 0){
        if (comparison(b) == 0){
            if (comparison(c) == 0){
                return INFINITEROOTS;
            }
            else{
                return ZEROROOTS;
            }
        }
        else{
            return korni_1(b, c, x1, x2);
        }
    }
    else{
        return korni_2(a,  b,  c,  x1,  x2);
    }
}



int korni_1(double k, double c, double* x1, double* x2)
{
    *x1 = *x2 = (-c)/k;
    return ONEROOT;
}



int korni_2(double a, double b, double c, double* x1, double* x2)
{
    double d = 0.0;
    d = b*b - 4*a*c;

    if (comparison(d) == -1){
        /*printf("ERROR: D < 0\n");*/
        return ZEROROOTS;
    }
    else if (comparison(d) == 0){
        *x1 = *x2 = (-b) / (2 * a);
        return ONEROOT;
    }
    else{
        *x1 = ((-b) + sqrt(d)) / (2 * a);
        *x2 = ((-b) - sqrt(d)) / (2 * a);
        return TWOROOTS;
    }
    return ERRORCONST;
}



void outp(int count_ans, double* x1, double* x2)
{
    int q = 0, w = 0;
    color(&q, &w);
    switch (count_ans){
    case 1:
        printf("One root\n");
        printf("\033[%d;3%dm " "%4.f \033[0m \n", q, w, *x1);
        break;
    case 2:
        printf("Two roots\n");
        printf("\033[%d;3%dm %4.2f, %6.2f \n \033[0m ",q, w, *x1, *x2);
        break;
    case 0:
        printf("\033[%d;3%dm No roots \n \033[0m", q, w);
        break;
    case 3:
        printf("\033[%d;3%dm ERROR: an infinite number of roots \n \033[0m", q, w);
        break;
    default:
        printf("\033[%d;3%dm ERROR: roots didnt read \n \033[0m", q, w);
        break;
    }

}



int comparison(double L)
{
    if (-EPSIL < L && L < EPSIL){
        return 0;
    }
    else if (L < -EPSIL){
        return -1;
    }
    else if (L > EPSIL){
        return 1;
    }
    else{
        printf("Wrong comparison, take lower const\n");
        return 0;
    }
}



void color(int* q, int* w)
{
    printf("What is your favourite font(shrift)?\n");
    printf("0 - reset\n1 - bold text\n4 - emphasized(podch))\n7 - invers\n");
    scanf("%d", q);

    printf("What is your favourite color?\n");
    printf("0 - black\t1 - red\t2 - green\n3 - yellow\t4 - blue\t5 - purple\n6 - light blue\t7 - white.\n");

    scanf("%d", w);
}



int number_of_tests(int* number_of_t)
{
    printf("How much tests do you want to do?\n");
    printf("Max tests - %d\n", ITERATIONS);
    scanf("%d", number_of_t);
    return 0;
}
