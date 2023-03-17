#include <check.h>

#include "../s21_matrix.h"

static matrix_t A;
static matrix_t result;
static matrix_t expect;
static int is_equal;
static int status;

static void setup(void) {
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &expect);
  is_equal = -99;
  status = -99;
}

static void teardown(void) {
  s21_remove_matrix(&A);
  s21_remove_matrix(&expect);
  s21_remove_matrix(&result);
}

static void fill_matrix(double **A, matrix_t *matrix, int rows, int columns) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix->matrix[i][j] = *((double *)(A + i * columns) + j);
    }
  }
}

START_TEST(test_empty_matrix_return_empty_wit_correct_dimension) {
  status = s21_transpose(&A, &result);

  is_equal = s21_eq_matrix(&result, &expect);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_transposed_ok) {
  //           1 4   1 2 3
  // A = A^T = 2 5 = 4 5 6
  //           3 6
  double a_matrix[3][2] = {
      {1, 4},
      {2, 5},
      {3, 6},
  };
  double expect_matrix[2][3] = {
      {1, 2, 3},
      {4, 5, 6},
  };
  fill_matrix((double **)a_matrix, &A, A.rows, A.columns);
  fill_matrix((double **)expect_matrix, &expect, expect.rows, expect.columns);

  status = s21_transpose(&A, &result);

  is_equal = s21_eq_matrix(&result, &expect);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_matrix_bad) {
  A.rows = 0;  // Makes matrix incorrect

  status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_result_null_pointer) {
  matrix_t *null_ptr = NULL;

  status = s21_transpose(&A, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

Suite *make_suite_s21_transpose(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_empty_matrix_return_empty_wit_correct_dimension);
  tcase_add_test(tc, test_transposed_ok);
  tcase_add_test(tc, test_return_bad_matrix_if_matrix_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_result_null_pointer);

  return s;
}
