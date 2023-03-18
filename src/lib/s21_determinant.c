#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  // Edge cases
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  // Regular case
  int size = A->rows;
  if (size == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t minor_matrix;
    double minor_determinant = 0;
    double sub_result = 0;
    for (int j = 0, sign = 1; j < size; ++j) {
      s21_minor_matrix(A, 0, j, &minor_matrix);  // Calculate by first row
      s21_determinant(&minor_matrix, &minor_determinant);
      sub_result += sign * A->matrix[0][j] * minor_determinant;
      s21_remove_matrix(&minor_matrix);
      sign *= -1;
    }
    *result = sub_result;
  }

  return OK;
}
