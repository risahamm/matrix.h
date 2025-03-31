# s21_matrix

Реализация библиотеки matrix.h. Учебный проект.

- Библиотека разработана на языке Си стандарта C11 с использованием компилятора gcc
- Код библиотеки находится в папке src в ветке develop
- Код написан в соответствии с Google Style
- Оформить решение как статическую библиотеку (с заголовочным файлом s21_matrix.h)
- Библиотека разработана в соответствии с принципами структурного программирования
- Подготовлено полное покрытие unit-тестами c помощью библиотеки <check.h>
- Предусмотрен Makefile для сборки библиотеки с целями all, clean, test, s21_matrix.a, gcov_report
- Проверяемая точность дробной части - максимум 7 знаков после запятой

### Структура матрицы:

```c
typedef struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Операции над матрицами

Все операции (кроме сравнения матриц) должны возвращать результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

| Function                                                            | Description                       |
|---------------------------------------------------------------------|-----------------------------------|
| `int s21_create_matrix(int rows, int columns, matrix_t *result)`    | Создание матриц                   |  
| `void s21_remove_matrix(matrix_t *A)`                               | Очистка матриц                    |
| `int s21_eq_matrix(matrix_t *A, matrix_t *B)`                       | Сравнение матриц                  |
| `int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`    | Сложение матриц                   |
| `int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`    | Вычитание матриц                  |
| `int s21_mult_number(matrix_t *A, double number, matrix_t *result)` | Умножение матрицы на число        |
| `int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`   | Умножение двух матриц             |
| `int s21_transpose(matrix_t *A, matrix_t *result)`                  | Транспонирование матрицы          |
| `int s21_calc_complements(matrix_t *A, matrix_t *result)`           | Матрица алгебраических дополнений |
| `int s21_determinant(matrix_t *A, double *result)`                  | Определитель матрицы              |
| `int s21_inverse_matrix(matrix_t *A, matrix_t *result)`             | Обратная матрица                  |