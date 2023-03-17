#include "../s21_matrix.h"

static double **calloc_matrix(uint32_t rows, uint32_t columns) {
  // All the validations has to be done outside this function
  // Create and return pointer to 2 dimensional array filled with 0

  double **matrix = (double **)malloc(sizeof(double *) * rows +
                                      sizeof(double) * rows * columns);

  if (matrix == NULL) {
    perror("Couldn't allocate memory for the matrix");
    exit(0);
  }

  double *matrix_data_ptr = (double *)(matrix + rows);

  for (uint32_t i = 0; i < rows; i++) {
    matrix[i] = matrix_data_ptr + columns * i;
    for (uint32_t j = 0; j < columns; j++) {
      matrix[i][j] = 0.0;
    }
  }

  return matrix;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) return INCORRECT_MATRIX;
  if (result == NULL) return INCORRECT_MATRIX;

  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc_matrix(rows, columns);

  return OK;
}
