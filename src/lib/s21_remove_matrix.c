#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *matrix) {
  if (matrix != NULL) {
    if (matrix->matrix != NULL) free(matrix->matrix);
    matrix->columns = 0;
    matrix->rows = 0;
    matrix->matrix = NULL;
  }
}
