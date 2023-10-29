#include "s21_matrix.h"

int check_matrix(matrix_t *A) {
  return (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1);
}

int create_minor(matrix_t *A, int delete_row, int delete_column,
                 matrix_t *result) {
  int return_code = OK;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, result) == OK) {
    int res_row = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == delete_row) continue;
      int res_column = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j == delete_column) continue;
        result->matrix[res_row][res_column] = A->matrix[i][j];
        res_column++;
      }
      res_row++;
    }
  } else
    return_code = INCORRECT;
  return return_code;
}

// void print_matrix(matrix_t *A) {
//   if (A->matrix == NULL) {
//   }
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++) {
//       printf("%10.7lf ", A->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
