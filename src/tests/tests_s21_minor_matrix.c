#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;
static matrix_t result;
static matrix_t expected;
static int is_equal;
static int status;

static void fill_matrix(double **A, matrix_t *matrix) {
  int rows = matrix->rows;
  int columns = matrix->columns;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix->matrix[i][j] = *((double *)(A + i * columns) + j);
    }
  }
}

static void setup(void) {
  s21_create_matrix(4, 4, &matrix);
  s21_create_matrix(3, 3, &expected);
  is_equal = -99;
  status = -99;

  double initial_matrix_values[4][4] = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16},
  };

  fill_matrix((double **)initial_matrix_values, &matrix);
}

static void teardown(void) {
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}

START_TEST(test_minor_matrix_first_element) {
  double expected_value[3][3] = {
      {6, 7, 8},
      {10, 11, 12},
      {14, 15, 16},
  };
  fill_matrix((double **)expected_value, &expected);

  status = s21_minor_matrix(&matrix, 0, 0, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_minor_matrix_middle_element) {
  double expected_value[3][3] = {
      {1, 3, 4},
      {5, 7, 8},
      {13, 15, 16},
  };
  fill_matrix((double **)expected_value, &expected);

  status = s21_minor_matrix(&matrix, 2, 1, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_matrix_bad) {
  matrix.rows = 0;  // Makes matrix incorrect

  status = s21_minor_matrix(&matrix, 0, 0, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_result_null) {
  matrix_t *null_ptr = NULL;

  status = s21_minor_matrix(&matrix, 0, 0, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_calculation_error_if_not_square) {
  matrix.columns = 3;  // Has 4 rows == not square

  status = s21_minor_matrix(&matrix, 0, 0, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calc_error_if_row_less_zero) {
  status = s21_minor_matrix(&matrix, -1, 0, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calc_error_if_row_bigger_than_max_allowed) {
  status = s21_minor_matrix(&matrix, 4, 0, &result);  // Max allowed 3

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calc_error_if_column_less_zero) {
  status = s21_minor_matrix(&matrix, 0, -1, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calc_error_if_column_bigger_than_max_allowed) {
  status = s21_minor_matrix(&matrix, 0, 4, &result);  // Max allowed 3

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *make_suite_s21_minor_matrix(void) {
  Suite *s = suite_create("s21_minor_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_minor_matrix_first_element);
  tcase_add_test(tc, test_minor_matrix_middle_element);
  tcase_add_test(tc, test_return_bad_matrix_if_matrix_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_result_null);
  tcase_add_test(tc, test_return_calculation_error_if_not_square);
  tcase_add_test(tc, test_return_calc_error_if_row_less_zero);
  tcase_add_test(tc, test_return_calc_error_if_row_bigger_than_max_allowed);
  tcase_add_test(tc, test_return_calc_error_if_column_less_zero);
  tcase_add_test(tc, test_return_calc_error_if_column_bigger_than_max_allowed);

  return s;
}
