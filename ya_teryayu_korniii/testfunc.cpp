#include <stdio.h>
#include <math.h>

const char* name_file = "references.txt";
FILE* fp = fopen(name_file, "r");




//MENTOR -пернсти объявление функции getanswer
int getanswer(double a, double b, double c, double* x1, double* x2);


#define ITERATIONS 8
#define EPSILON4 0.00001


struct TestCase
{
    double a, b, c;
    int nRootsRef;
    double x1Ref, x2Ref;
};


const char* ErrorOrder = R"(
Error test№ %d: wrong order of roots
expected: roots %d   x1 = %lg   x2 = %lg
got:      roots %d   x1 = %lg   x2 = %lg
)";
const char* ErrorNumberRoots = R"(
Error test№ %d: wrong number of roots
expected: roots %d
got:      roots %d
)";
const char* WrongRooots = R"(
Error test№ %d: wrong roots
expected: roots %d   x1 = %lg   x2 = %lg
got:      roots %d   x1 = %lg   x2 = %lg
)";


int OneTest(TestCase references, int i);
int RunTests(int number_of_tests);
int not_same(double got, double ref);
int same(double got, double ref);
void print_struct(TestCase references);
void get_stract(TestCase* ref);



int OneTest(TestCase references, int i)
{
    double x1 = NAN, x2 = NAN;
    int nRoots = getanswer(references.a, references.b, references.c, &x1, &x2);

    if (isnan(x1) && isnan(references.x1Ref) == 0){
        printf("Error%d: root x1 didnt change from nan\n\n", i);
        return 0;
    }
    else if(isnan(x2) && isnan(references.x2Ref) == 0){
        printf("Error%d: root x2 didnt change from nan\n\n", i);
        return 0;
    }
    else if (not_same(nRoots, references.nRootsRef)){
        printf(ErrorNumberRoots, i, references.nRootsRef, nRoots);
        return 0;
    }
    else if (same(x1, references.x2Ref) && same(x2, references.x1Ref) && not_same(x1, x2)){
        printf(ErrorOrder, i, references.nRootsRef, references.x1Ref, references.x2Ref, nRoots, x1, x2);
        return 0;
    }
    else if ((not_same(x1, references.x1Ref) || not_same(x2, references.x2Ref)) && isnan(references.x1Ref) == 0 && isnan(references.x2Ref) == 0){
        printf(WrongRooots, i, references.nRootsRef, references.x1Ref, references.x2Ref, nRoots, x1, x2);
        return 0;
    }
    return 1;
}



int RunTests(int number_of_tests)
{
    int right_tests = 0, i = 0;
    TestCase references = {};
    TestCase* ref = &references;

    get_stract(ref);

    if (number_of_tests >= ITERATIONS)
        number_of_tests = ITERATIONS;

    for (i = 0; i < number_of_tests; i ++){
        /*pprintf("\n\n\nIteration %d\n", i);
        rintf("Struct To OneTest ");
        print_struct(references[i]);*/

        int test = OneTest(references, i);
        right_tests += test;
    }
    return right_tests;
}



int not_same(double got, double ref)
{
    if (fabs(got - ref) < EPSILON4)
        return 0;
    else
        return 1;
}



int same(double got, double ref)
{
    return fabs(got - ref) < EPSILON4;
}



void print_struct(TestCase references)
{
    printf("a = %lg b = %lg c = %lg nRootsRef = %d x1Ref = %lg x2Ref = %lg\n", references.a, references.b, references.c, references.nRootsRef, references.x1Ref, references.x2Ref);
}


//NOTE - get git a
 void get_stract(TestCase* ref)
{
    double a = 0.0, b = 0.0, c = 0.0, x1Ref = 0.0, x2Ref = 0.0;
    int nRootsRef = 0;

    fscanf(fp, "%lg %lg %lg %d %lg %lg", &a, &b, &c, &nRootsRef, &x1Ref, &x2Ref);
    *ref = {a, b, c, nRootsRef, x1Ref, x2Ref};
}
