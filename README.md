# s21_matrix  

Implementation of the matrix.h library. Study project.

- The library is developed in C language of C11 standard using gcc compiler
- The library code is located in the src folder on the develop branch
- The code of the program is written in accordance with Google style 
- Static library (with the s21_matrix.h header file)
- The library is developed according to the principles of structured programming
- Full coverage of library functions code provided with unit-tests using <check.h> library
- Makefile with targets all, clean, test, s21_matrix.a, gcov_report is provided
- Verifiable accuracy of the fractional part is up to 7 decimal points

### Matrix structure:

```c
typedef struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```
## Matrix operations

All operations (except matrix comparison) return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

| Function                                                            | Description                     |
|---------------------------------------------------------------------|---------------------------------|
| `int s21_create_matrix(int rows, int columns, matrix_t *result)`    | Creating matrices               |  
| `void s21_remove_matrix(matrix_t *A)`                               | Cleaning matrices               |
| `int s21_eq_matrix(matrix_t *A, matrix_t *B)`                       | Matrix comparison               |
| `int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`    | Adding matrices                 |
| `int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`    | Subtracting matrices            |
| `int s21_mult_number(matrix_t *A, double number, matrix_t *result)` | Matrix multiplication by scalar |
| `int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)`   | Multiplication of two matrices  |
| `int s21_transpose(matrix_t *A, matrix_t *result)`                  | Matrix transpose                |
| `int s21_calc_complements(matrix_t *A, matrix_t *result)`           | Matrix of algebraic complements |
| `int s21_determinant(matrix_t *A, double *result)`                  | Matrix determinant              |
| `int s21_inverse_matrix(matrix_t *A, matrix_t *result)`             | Inverse of the matrix           |