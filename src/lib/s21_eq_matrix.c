#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Edge cases
  if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B)) return FAILURE;
  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  // Regular case
  int is_equal = SUCCESS;
  for (int i = 0; i < A->rows && is_equal; ++i) {
    for (int j = 0; j < A->columns && is_equal; ++j) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > S21_EPSILON) {
        is_equal = FAILURE;
      }
    }
  }

  return is_equal;
}
