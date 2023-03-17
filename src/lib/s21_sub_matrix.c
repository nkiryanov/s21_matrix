#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Edge cases
  if (!s21_validate_matrix(A) || !s21_validate_matrix(B)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCULATION_ERROR;

  // Regular case
  int rows = A->rows;
  int columns = A->columns;
  s21_create_matrix(rows, columns, result);  // Impossible to return error

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}
