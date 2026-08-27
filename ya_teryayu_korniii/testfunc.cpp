#include "testfunc.h"
#include "main.h"

int run_one_test(TestCase references, int i);
int write_one_test_to_ref(const char* NAME_FILE_CONST);
bool is_equal(double got, double ref);
void print_TestCase_struct(TestCase references);
void get_tests(TestCase* references);

int run_one_test(TestCase references, int i) {
    double x1 = NAN, x2 = NAN;
    int number_of_roots = solve_equation(references.a, references.b, references.c, &x1, &x2);

    if (isnan(x1) && (isnan(references.x1Ref) == 0)){
        printf("Error%d: root x1 didnt change from nan\n\n", i);
        return 0;
    }
    else if (isnan(x2) && (isnan(references.x2Ref) == 0)){
        printf("Error%d: root x2 didnt change from nan\n\n", i);
        return 0;
    }
    else if (!is_equal(number_of_roots, references.number_of_roots_ref)){
        printf("Error test№ %d: wrong number of roots\n"
            "expected: roots = %d\n"
            "got:      roots = %d\n",
            i, references.number_of_roots_ref, number_of_roots);
        return 0;
    }
    else if (((!is_equal(x1, references.x1Ref) && !is_equal(x2, references.x1Ref))
            || (!is_equal(x2, references.x2Ref) && !is_equal(x1, references.x2Ref)))
            && isnan(references.x1Ref) == 0 && isnan(references.x2Ref) == 0) {
        printf("(Error test№ %d: wrong roots\n"
            "expected: roots = %d   x1 = %lg   x2 = %lg\n"
            "got:      roots = %d   x1 = %lg   x2 = %lg\n",
            i, references.number_of_roots_ref, references.x1Ref, references.x2Ref, number_of_roots, x1, x2);
        return 0;
    }
    return 1;
}

int run_all_tests(void) {
    int right_tests = 0, i = 0;

    TestCase references[ITERATIONS] = {};

    get_tests(references);

    for (i = 0; i < ITERATIONS; i ++){
        int test = run_one_test(references[i], i);
        right_tests += test;
    }

    return right_tests;
}

bool is_equal(double got, double ref) {
    const double EPSILON_3_CONST = 0.001;
    return fabs(got - ref) < EPSILON_3_CONST;
}

void print_TestCase_struct(TestCase references) {
    printf("a = %lg b = %lg c = %lg number_of_roots_ref = %d x1Ref = %lg x2Ref = %lg\n",
            references.a, references.b, references.c, references.number_of_roots_ref,
            references.x1Ref, references.x2Ref);
}

int write_one_test_to_ref(const char* NAME_FILE_CONST) {

    srand((unsigned int)(time(NULL)));//MENTOR смена типа,не меняющиеся значения
    double a = NAN, x1 = NAN, x2 = NAN;
                                        //NOTE диапазон значений rand [-50, 50]
    a = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;
    x1 = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;
    x2 = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;

    int number_of_roots = (is_equal(x1, x2)) ? 1 : 2;
    double b = - a * (x1 + x2);
    double c = a * x1 * x2;

    FILE* fp = fopen(NAME_FILE_CONST, "a");
    int result_state = fprintf(fp, "%lg %lg %lg %d %lg %lg\n", a, b, c, number_of_roots, x1, x2);
    fclose(fp);

    if (result_state)
        return 1;
    else
        return 0;
}

 void get_tests(TestCase* references) {
    const char* NAME_FILE_CONST = "references.txt";

    for (int number_generated_tests = 0; number_generated_tests < ITERATIONS * 2; number_generated_tests++) {
        int func_state = write_one_test_to_ref(NAME_FILE_CONST);

        assert(func_state == 1 && "ERROR in write_one_test_to_ref, wrong fprintf\n");
    }

    FILE* fp = fopen(NAME_FILE_CONST, "r");
    for (int j = 0; j < ITERATIONS; j++) {
        fscanf(fp, "%lg %lg %lg %d %lg %lg",
                &references[j].a, &references[j].b, &references[j].c, &references[j].number_of_roots_ref,
                &references[j].x1Ref, &references[j].x2Ref);
    }
    fclose(fp);
}
