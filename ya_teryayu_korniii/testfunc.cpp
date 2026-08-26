#include "testfunc.h"
#include "main.h"

int run_one_test(TestCase references, int i);
bool is_equal(double got, double ref);
int is_not_equal(double got, double ref);
void print_TestCase_struct(TestCase references);
void read_tests(TestCase* references);

int run_one_test(TestCase references, int i) {
    double x1 = NAN; //NOTE - remove when it started to work
    double x2 = NAN;
    int nRoots = solve_equation(references.a, references.b, references.c, &x1, &x2);

    if (isnan(x1) && (isnan(references.x1Ref) == 0)){
        printf("Error%d: root x1 didnt change from nan\n\n", i);
        return 0;
    }
    else if (isnan(x2) && (isnan(references.x2Ref) == 0)){
        printf("Error%d: root x2 didnt change from nan\n\n", i);
        return 0;
    }
    else if (is_not_equal(nRoots, references.nRootsRef)){
        printf("Error test№ %d: wrong number of roots\n"
            "expected: roots %d\n"
            "got:      roots %d\n",
            i, references.nRootsRef, nRoots);
        return 0;
    }
    else if (is_equal(x1, references.x2Ref) && is_equal(x2, references.x1Ref) && is_not_equal(x1, x2)){
        printf("Error test№ %d: wrong order of roots\n"
            "expected: roots %d   x1 = %lg   x2 = %lg\n"
            "got:      roots %d   x1 = %lg   x2 = %lg\n",
            i, references.nRootsRef, references.x1Ref, references.x2Ref, nRoots, x1, x2);
        return 0;
    }
    else if ((is_not_equal(x1, references.x1Ref) || is_not_equal(x2, references.x2Ref)) && isnan(references.x1Ref) == 0 && isnan(references.x2Ref) == 0){
        printf("(Error test№ %d: wrong roots\n"
            "expected: roots %d   x1 = %lg   x2 = %lg\n"
            "got:      roots %d   x1 = %lg   x2 = %lg\n",
            i, references.nRootsRef, references.x1Ref, references.x2Ref, nRoots, x1, x2);
        return 0;
    }

    return 1;
}

int run_all_tests(void) {
    int right_tests = 0, i = 0;

    TestCase references[ITERATIONS] = {};

    read_tests(references);

    for (i = 0; i < ITERATIONS; i ++){
        int test = run_one_test(references[i], i);
        right_tests += test;
    }

    return right_tests;
}

bool is_equal(double got, double ref) {
    const double EPSILON_4_CONST = 0.0001;
    return fabs(got - ref) < EPSILON_4_CONST;
}

int is_not_equal(double got, double ref) {
    return !is_equal(got, ref);
}

void print_TestCase_struct(TestCase references) {
    printf("a = %lg b = %lg c = %lg nRootsRef = %d x1Ref = %lg x2Ref = %lg\n",
            references.a, references.b, references.c, references.nRootsRef,
            references.x1Ref, references.x2Ref);
}

 void read_tests(TestCase* references) {
    const char* NAME_FILE_CONST_CONST = "references.txt";
    FILE* fp = fopen(NAME_FILE_CONST_CONST, "r");

    for (int j = 0; j < ITERATIONS; j++){
        fscanf(fp, "%lg %lg %lg %d %lg %lg",
                &references[j].a, &references[j].b, &references[j].c, &references[j].nRootsRef,
                &references[j].x1Ref, &references[j].x2Ref);
    }
}
