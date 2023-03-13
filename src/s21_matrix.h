#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum S21_BOOL {
  S21_FALSE,
  S21_TRUE,
};

#define FAILURE 0
#define SUCCESS 1

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

/* -----------------------------------------------------
---------------- Functions definitions -----------------
------------------------------------------------------ */

int s21_create_matrix(int rows, int columns, matrix_t* result);

#endif  // SRC_S21_MATRIX_H_
