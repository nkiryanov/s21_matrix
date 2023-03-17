#include "../s21_matrix.h"

int s21_is_valid_matrix(matrix_t *matrix) {
  return ((matrix == NULL) || (matrix->columns <= 0) || (matrix->rows <= 0) ||
          (matrix->matrix == NULL))
             ? S21_FALSE
             : S21_TRUE;
}
