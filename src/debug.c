#include "s21_matrix.h"
#include "stdio.h"

void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      printf("%lf ", A->matrix[i][j]);
    }
    printf("\n");
  }
}

static void fill_matrix(double **A, double **matrix, int rows, int columns) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix[i][j] = *((double *)(A + i * columns) + j);
    }
  }
}

int main() {
  matrix_t A;
  matrix_t expect;
  matrix_t result;

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &expect);

  double a_matrix[3][2] = {{1, 4}, {2, 5}, {3, 6}};
  double e_matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  fill_matrix((double **)a_matrix, A.matrix, A.rows, A.columns);
  fill_matrix((double **)e_matrix, expect.matrix, expect.rows, expect.columns);

  s21_transpose(&A, &result);

  print_matrix(&expect);
  print_matrix(&result);
}
