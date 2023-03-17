#include <check.h>

#include "../s21_matrix.h"

static matrix_t A;
static matrix_t B;
static matrix_t result;
static matrix_t expect;
static int is_equal;
static int status;

static void setup(void) {
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &expect);
  is_equal = -99;
  status = -99;
}

static void teardown(void) {
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expect);
  s21_remove_matrix(&result);
}

static void fill_matrix(double **A, double **matrix, int rows, int columns) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix[i][j] = *((double *)(A + i * columns) + j);
    }
  }
}

START_TEST(test_empty_compatible_matrices_return_empty_matrix) {
  status = s21_mult_matrix(&A, &B, &result);

  is_equal = s21_eq_matrix(&result, &expect);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_mult_all_rows_and_columns) {
  double a_matrix[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  double b_matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double e_matrix[3][3] = {{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
  fill_matrix((double **)a_matrix, A.matrix, A.rows, A.columns);
  fill_matrix((double **)b_matrix, B.matrix, B.rows, B.columns);
  fill_matrix((double **)e_matrix, expect.matrix, expect.rows, expect.columns);

  status = s21_mult_matrix(&A, &B, &result);

  is_equal = s21_eq_matrix(&result, &expect);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_first_bad) {
  A.rows = 0;  // Makes matrix incorrect

  status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_second_bad) {
  B.columns = 0;  // Makes matrix incorrect

  status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_result_null_pointer) {
  matrix_t *null_ptr = NULL;

  status = s21_mult_matrix(&A, &B, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_calculation_error_if_matrices_not_complements) {
  A.columns = 1;  // B has 2 rows

  status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_no_errors_if_matrices_complements) {
  A.columns = 1;
  B.rows = 1;

  status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
}
END_TEST

Suite *make_suite_s21_mult_matrix(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_empty_compatible_matrices_return_empty_matrix);
  tcase_add_test(tc, test_mult_all_rows_and_columns);
  tcase_add_test(tc, test_return_bad_matrix_if_first_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_second_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_result_null_pointer);
  tcase_add_test(tc, test_return_calculation_error_if_matrices_not_complements);
  tcase_add_test(tc, test_no_errors_if_matrices_complements);

  return s;
}
