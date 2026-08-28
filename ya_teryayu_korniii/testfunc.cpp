#include "testfunc.h"
#include "main.h"

#define RANGE_LENGTH 100
#define RANGE_MAXIMUM 50
#define NUMBER_TESTS 20

int run_one_test(TestCase references, int i);//TODO написать ручные тесты,
int get_tests(TestCase* references, FILE* fp, char* test_mode);
int get_generated_tests(TestCase* generated_ref);
int generate_one_test(TestCase* references, int seed, int num_test);
int get_manual_tests(FILE* fp, TestCase* references);
void print_TestCase_struct(TestCase references);
bool is_equal(double got, double ref);

//const char* name_file = "";

int run_all_tests(char* name_file, char* test_mode) {
    assert(name_file != NULL && "ERROR wrong name_file");
    assert(test_mode != NULL && "ERROR wrong test_mode");

    FILE* fp = fopen(name_file, "r");

    int right_tests = 0, i = 0;

    TestCase references[NUMBER_TESTS] = {};

    int status_get_tests = get_tests(references, fp, test_mode);
    assert(status_get_tests == 0 && "ERROR in get_tests function");

    for (i = 0; i < NUMBER_TESTS; i ++){
        int test = run_one_test(references[i], i);
        right_tests += test;
    }
    fclose(fp);
    return right_tests;
}

int get_tests(TestCase* references, FILE* fp, char* test_mode) {
    assert(references != NULL && "ERROR wrong references");
    assert(fp != NULL && "ERROR wrong fp");
    assert(test_mode != NULL && "ERROR wrongtest_mode");

    if (!(strcmp(test_mode, "auto"))) {
        get_generated_tests(references);
        return 0;
    }
    if (!(strcmp(test_mode, "manual"))) {
        get_manual_tests(fp, references); // MENTOR проверка правильности с помощью return
        return 0;
    }
    return 1;
}

int get_generated_tests(TestCase* references) {
    assert(references != NULL && "ERROR wrong references");

    srand((unsigned int)time(NULL));
    int seed = rand()%(10);

    for (int num_test = 0; num_test < NUMBER_TESTS; num_test++) {
        seed += 1;
        int func_state = generate_one_test(references, seed, num_test);

        assert(func_state == 0 && "ERROR in generate_one_test, wrong fprintf\n");
    }
    return 0;
}

int generate_one_test(TestCase* references, int seed, int num_test) {
    assert(references != NULL && "ERROR wrong references");

    srand((unsigned int)seed); // MENTOR  type
    double a = NAN, x1 = NAN, x2 = NAN;
                                        //NOTE диапазон значений rand [-50, 50]
    a = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;
    x1 = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;
    x2 = ((double) rand() / (RAND_MAX+1.0)) * RANGE_LENGTH - RANGE_MAXIMUM;

    int number_of_roots = (is_equal(x1, x2)) ? 1 : 2;
    double b = - a * (x1 + x2);
    double c = a * x1 * x2;

    references[num_test] = {.a = a, .b = b, .c = c,
        .number_of_roots_ref = number_of_roots, .x1Ref = x1, .x2Ref = x2};
    return 0;
}

int get_manual_tests(FILE* fp, TestCase* references) {
    assert(fp != NULL && "ERROR wrong fp");
    assert(references != NULL && "ERROR wrong references");

    for (int num_test = 0; num_test < NUMBER_TESTS; num_test++){
        fscanf(fp, "%lg %lg %lg %d %lg %lg", &references[num_test].a, &references[num_test].b,
            &references[num_test].c, &references[num_test].number_of_roots_ref,
            &references[num_test].x1Ref, &references[num_test].x2Ref);
    }
    return 0;
}

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

bool is_equal(double got, double ref) {
    const double EPSILON_3_CONST = 0.001;
    return fabs(got - ref) < EPSILON_3_CONST;
}

void print_TestCase_struct(TestCase references) {
    printf("a = %lg b = %lg c = %lg number_of_roots_ref = %d x1Ref = %lg x2Ref = %lg\n",
            references.a, references.b, references.c, references.number_of_roots_ref,
            references.x1Ref, references.x2Ref);
}
