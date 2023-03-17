#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Edge cases
  if (!s21_validate_matrix(A) || !s21_validate_matrix(B)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;
  if (A->columns != B->rows) return CALCULATION_ERROR;

  // Regular case
  int rows = A->rows;
  int columns = B->columns;
  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}
