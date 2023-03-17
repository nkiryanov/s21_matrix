#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;

  int rows = A->columns;
  int columns = A->rows;
  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }

  return OK;
}
