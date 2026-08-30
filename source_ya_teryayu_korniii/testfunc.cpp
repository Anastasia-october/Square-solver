/**
    \file
    \brief Release testing. Is called by main
    \details Launches manual or randomly generated tests. The choice of mode depends on the command-line argument.
    Function run_all_tests() is called by main() from main.cpp. Calls enum roots_flags solve_equation() form main.cpp to get roots.
    Other functions are called from function run_all_tests() or from functions called by it.


 */
#include <errno.h>
#include "testfunc.h"
#include "main.h"

#define RANGE_LENGTH 100
#define RANGE_MAXIMUM 50
#define NUMBER_TESTS 20

int run_one_test(TestCase references, int i);//TODO написать ручные тесты,
int get_tests(TestCase* references, FILE* fp, char* test_mode);
int get_generated_tests(TestCase* generated_ref);
void generate_one_test(TestCase* references, int seed, int num_test);
int get_manual_tests(FILE* fp, TestCase* references);
void print_TestCase_struct(TestCase references);
bool is_equal(double got, double ref);
void error_monitor(void);

//const char* name_file = "";

/**
    Вызывает функцию для получения тестовых данных и функцию для исполнения одного теста
    \param[out] right_tests Количество верно пройденных тестов
    \param[in] name_file Имя файла с написанными вручную тестами
    \param[in] test_mode Режим тестирования(написанные вручную или сгенерированные тесты)
    \return right_tests - количество верно пройденных тестов
*/
int run_all_tests(char* name_file, char* test_mode) {
    assert(name_file != NULL && "ERROR wrong name_file");
    assert(test_mode != NULL && "ERROR wrong test_mode");

    FILE* fp = fopen(name_file, "r");
    error_monitor();

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

/**
    Вызывает функцию get_generated_tests() или get_manual_tests() в зависимости от параметра test_mode
    \param[in] references Указатель на массив структур TestCase хранящих набор тестовых данных
    \param[in] fp Указатель на файл, в котором записаны тесты
    \param[in] test_mode Указатель на массив символов (строку), от которого зависит режим тестирования

    \return 0 если тесты записаны в структуру
    \return 1 если режим тестирования неизвестен, тесты в структуру не записаны
 */
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

/**
    Задаёт начальное число для генератора и вызывает функцию generate_one_test() в цикле NUMBER_TESTS раз. NUMBER_TESTS смотри в define
    \param[in] references Указатель на массив структур TestCase
 */
int get_generated_tests(TestCase* references) {
    assert(references != NULL);

    srand((unsigned int)time(NULL));
    int seed = rand()%(10);

    for (int num_test = 0; num_test < NUMBER_TESTS; num_test++) {
        seed += 1;
        generate_one_test(references, seed, num_test);
    }
    return 0;
}

/**
    Генерирует старший коэффициент и корни квадратного уравнения.
    Проверяет количество корней и рассчитывает средний коэффициент и свободный член уравнения по теореме Виета.
    Записывает полученные тестовые данные в структуру TestCase,находящуюся в массиве references
    \param [in] references Указатель на массив структур TestCase
    \param [in] seed Начальное число для генератора
    \param [in] num_test Индекс структуры в массиве references, в которую записываются данные
 */
void generate_one_test(TestCase* references, int seed, int num_test) {
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
}

/**
    Читает написанные вручную тесты из файла и записывает данные в структуры, находящиеся в массиве.
    \param [in] fp Указатель на файл с написанными вручную тестами
    \param [in] references Указатель на массив структур с тестовыми данными
 */
int get_manual_tests(FILE* fp, TestCase* references) {
    assert(fp != NULL && "ERROR wrong fp");
    assert(references != NULL && "ERROR wrong references");

    for (int num_test = 0; num_test < NUMBER_TESTS; num_test++){
        fscanf(fp, "%lg %lg %lg %d %lg %lg", &references[num_test].a, &references[num_test].b,
            &references[num_test].c, &references[num_test].number_of_roots_ref,
            &references[num_test].x1Ref, &references[num_test].x2Ref);
        error_monitor();
    }
    return 0;
}

/**
    Запускает один тест, вызывая функцию solve_equation() из файла main.cpp.
    Получает значение i - номер теста, для печати в случае ошибки при выполнение теста

    Проверяет \n
    1) были ли присвоены корням новые значения \n
    2) правильное ли количество корней \n
    3) правильные ли корни
    \param [in] references
    \param [in] i
    \return 0
    \return 1
 */
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

/**
    Сравнивает числа с плавающей точкой с точностью EPSILON
    \param [in] got Число 1
    \param [in] ref Число 2
    \return bool
 */
bool is_equal(double got, double ref) {
    const double EPSILON = 0.001;
    return fabs(got - ref) < EPSILON;
}

/**
    печатает структуру TestCase
    \param[in] references Структура TestCase
 */
void print_TestCase_struct(TestCase references) {
    printf("a = %lg b = %lg c = %lg number_of_roots_ref = %d x1Ref = %lg x2Ref = %lg\n",
            references.a, references.b, references.c, references.number_of_roots_ref,
            references.x1Ref, references.x2Ref);
}

void error_monitor(void) {
    if (errno)
        perror("Failed: ");
}
