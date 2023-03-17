#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;

  int rows = A->rows;
  int columns = A->columns;
  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return OK;
}
