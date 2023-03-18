#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Edge cases
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  // Regular cases
  int rows = A->rows;
  int columns = A->columns;
  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix_t minor;
      double minor_determinant = 0;
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      s21_minor_matrix(A, i, j, &minor);
      s21_determinant(&minor, &minor_determinant);
      result->matrix[i][j] = minor_determinant * sign;

      s21_remove_matrix(&minor);
    }
  }

  return OK;
}
