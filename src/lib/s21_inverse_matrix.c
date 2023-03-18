#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_validate_matrix(A)) return BAD_MATRIX;
  if (result == NULL) return BAD_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  double determinant = 0;
  s21_determinant(A, &determinant);
  if (fabs(determinant) < S21_EPSILON) return CALCULATION_ERROR;

  int size = A->rows;
  matrix_t complements;
  matrix_t transposed_complements;

  s21_calc_complements(A, &complements);
  s21_transpose(&complements, &transposed_complements);
  s21_remove_matrix(&complements);

  s21_create_matrix(size, size, result);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result->matrix[i][j] = transposed_complements.matrix[i][j] / determinant;
    }
  }

  s21_remove_matrix(&transposed_complements);
  return OK;
}
