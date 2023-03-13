#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;

static void setup(void) {
  matrix.rows = -99;
  matrix.columns = -99;
  matrix.matrix = NULL;
}

static void teardown(void) {
  if (matrix.matrix != NULL) {
    free(matrix.matrix);
  }
}

static int check_matrix_filled_nulls(matrix_t *matrix) {
  int is_matrix_nulled = S21_TRUE;

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      if (matrix->matrix[i][j] != 0) is_matrix_nulled = S21_FALSE;
    }
  }

  return is_matrix_nulled;
}

START_TEST(test_create_matrix_expected_size) {
  int status = s21_create_matrix(10, 11, &matrix);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(matrix.rows, 10);
  ck_assert_int_eq(matrix.columns, 11);
}
END_TEST

START_TEST(test_create_matrix_filled_with_nulls) {
  int status = s21_create_matrix(10, 11, &matrix);

  int is_matrix_nulled = check_matrix_filled_nulls(&matrix);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_matrix_nulled, S21_TRUE);
}
END_TEST

START_TEST(test_return_error_when_rows_less_or_zero) {
  int status = s21_create_matrix(0, 11, &matrix);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_return_error_when_columns_less_or_zero) {
  int status = s21_create_matrix(11, 0, &matrix);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_return_error_when_if_matrix_it_pointer_to_null) {
  int status = s21_create_matrix(11, 20, NULL);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

Suite *make_suite_s21_create_matrix(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_create_matrix_expected_size);
  tcase_add_test(tc, test_create_matrix_filled_with_nulls);
  tcase_add_test(tc, test_return_error_when_rows_less_or_zero);
  tcase_add_test(tc, test_return_error_when_columns_less_or_zero);
  tcase_add_test(tc, test_return_error_when_if_matrix_it_pointer_to_null);

  return s;
}
