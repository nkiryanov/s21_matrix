#include "../s21_matrix.h"

int s21_minor_matrix(matrix_t *A, int row, int column, matrix_t *result) {
  // Edge cases
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  if (row < 0 || row >= A->rows) return CALCULATION_ERROR;
  if (column < 0 || column >= A->columns) return CALCULATION_ERROR;

  // Regular case
  s21_create_matrix(A->rows - 1, A->columns - 1, result);

  for (int i = 0, minor_i = 0; i < A->rows; ++i) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < A->columns; ++j) {
      if (j == column) continue;
      result->matrix[minor_i][minor_j] = A->matrix[i][j];
      ++minor_j;
    }
    ++minor_i;
  }

  return OK;
}
