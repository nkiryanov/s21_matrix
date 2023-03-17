#include "../s21_matrix.h"
#include "stdio.h"

void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      printf("%lf ", A->matrix[i][j]);
    }
    printf("\n");
  }
}
