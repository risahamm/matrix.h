#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) {
    return INCORRECT;
  }
  result->rows = 0;
  result->columns = 0;
  result->matrix = NULL;
  int return_code = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    result->rows = 0;
    result->columns = 0;
    return_code = INCORRECT;
  } else {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        return_code = INCORRECT;
        break;
      }
    }
  }
  return return_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (!A || !A->matrix) return;
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
  }
  if (A->matrix != NULL) {
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return FAILURE;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }
  int return_code = SUCCESS;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        return_code = FAILURE;
        break;
      }
    }
  }
  return return_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (check_matrix(A) || result == NULL || isnan(number)) {
    return INCORRECT;
  }
  int return_code = OK;
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }

  } else
    return_code = INCORRECT;
  return return_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || result == NULL) {
    return INCORRECT;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return ERROR;
  }
  int return_code = OK;
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else
    return_code = INCORRECT;
  return return_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || result == NULL) {
    return INCORRECT;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return ERROR;
  }
  int return_code = OK;
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else
    return_code = INCORRECT;
  return return_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || result == NULL) {
    return INCORRECT;
  }
  int return_code = OK;
  if (s21_create_matrix(A->columns, A->rows, result) == OK) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else
    return_code = INCORRECT;
  return return_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || result == NULL) {
    return INCORRECT;
  }
  int return_code = OK;
  if (A->columns == B->rows) {
    if (s21_create_matrix(A->rows, B->columns, result) == OK) {
      for (int k = 0; k < B->columns; k++) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->rows; j++) {
            result->matrix[i][k] += A->matrix[i][j] * B->matrix[j][k];
          }
        }
      }
    } else
      return_code = INCORRECT;
  } else
    return_code = ERROR;
  return return_code;
}

int s21_determinant(matrix_t *A, double *result) {
  if (check_matrix(A) || result == NULL) {
    return INCORRECT;
  }
  if (A->rows != A->columns) {
    return ERROR;
  }
  int return_code = OK;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[1][0] * A->matrix[0][1]);
  } else {
    *result = 0;
    for (int i = 0; i < A->columns; i++) {
      matrix_t temp = {0};
      int minor = create_minor(A, 0, i, &temp);
      double temp_determinant = 0;
      if (s21_determinant(&temp, &temp_determinant) == OK && minor == OK) {
        *result += A->matrix[0][i] * temp_determinant * pow(-1, i);
        s21_remove_matrix(&temp);
      } else
        return_code = ERROR;
    }
  }
  return return_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || result == NULL) {
    return INCORRECT;
  }
  if (A->rows != A->columns) {
    return ERROR;
  }
  int return_code = OK;
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) == OK)
      result->matrix[0][0] = A->matrix[0][0];
    else
      return_code = INCORRECT;
  } else if (A->rows > 1 &&
             s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t temp = {0};
        double determinant = 0;
        int minor = create_minor(A, i, j, &temp);
        if (s21_determinant(&temp, &determinant) == OK && minor == OK) {
          result->matrix[i][j] = determinant * pow(-1, (i + j));
          s21_remove_matrix(&temp);
        } else
          return_code = ERROR;
      }
    }
  } else
    return_code = INCORRECT;
  return return_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || result == NULL) {
    return INCORRECT;
  }
  if (A->rows != A->columns) {
    return ERROR;
  }
  int return_code = OK;
  double determinant = 0;
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) == OK)
      result->matrix[0][0] = 1 / A->matrix[0][0];
    else
      return_code = INCORRECT;
  } else if (A->rows > 1 && s21_determinant(A, &determinant) == OK) {
    matrix_t complements = {0};
    if (determinant != 0 && s21_calc_complements(A, &complements) == OK) {
      matrix_t transposed = {0};
      if (s21_transpose(&complements, &transposed) == OK) {
        if (s21_mult_number(&transposed, (1 / determinant), result) == OK) {
          return_code = OK;
          s21_remove_matrix(&transposed);
          s21_remove_matrix(&complements);
        } else
          return_code = ERROR;
      } else
        return_code = ERROR;
    } else
      return_code = ERROR;
  } else
    return_code = ERROR;
  return return_code;
}
