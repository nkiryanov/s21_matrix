#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum S21_BOOL {
  S21_FALSE,
  S21_TRUE,
};

#define S21_EPSILON 1e-7

#define FAILURE 0
#define SUCCESS 1

#define OK 0
#define BAD_MATRIX 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

#define EMPTY_MATRIX {NULL, 0, 0}

/* -----------------------------------------------------
---------------- Functions definitions -----------------
------------------------------------------------------ */

int s21_create_matrix(int rows, int columns, matrix_t* result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
void s21_remove_matrix(matrix_t* matrix);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_validate_matrix(matrix_t *matrix);

#endif  // SRC_S21_MATRIX_H_
