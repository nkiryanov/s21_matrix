#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;
static int is_valid;

static void setup(void) {
  s21_create_matrix(2, 3, &matrix);
  is_valid = -99;
}

static void teardown(void) { s21_remove_matrix(&matrix); }

START_TEST(test_regular_matrix_valid) {
  is_valid = s21_validate_matrix(&matrix);

  ck_assert_int_eq(is_valid, S21_TRUE);
}
END_TEST

START_TEST(test_manually_created_matrix_valid) {
  double matrix_array[2][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  matrix_t manual_matrix = {
      .rows = 2,
      .columns = 3,
      .matrix = (double **)matrix_array,
  };

  is_valid = s21_validate_matrix(&manual_matrix);

  ck_assert_int_eq(is_valid, S21_TRUE);
}
END_TEST

START_TEST(test_false_if_rows_null) {
  matrix.rows = 0;

  is_valid = s21_validate_matrix(&matrix);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

START_TEST(test_false_if_rows_less_zero) {
  matrix.rows = -1;

  is_valid = s21_validate_matrix(&matrix);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

START_TEST(test_false_if_columns_null) {
  matrix.columns = 0;

  is_valid = s21_validate_matrix(&matrix);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

START_TEST(test_false_if_columns_less_zero) {
  matrix.columns = -1;

  is_valid = s21_validate_matrix(&matrix);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

START_TEST(test_false_if_submatrix_pointer_to_null) {
  matrix_t matrix_to_null = {.rows = 2, .columns = 3, .matrix = NULL};

  is_valid = s21_validate_matrix(&matrix_to_null);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

START_TEST(test_false_if_matrix_pointer_to_null) {
  matrix_t *matrix_ptr = NULL;

  is_valid = s21_validate_matrix(matrix_ptr);

  ck_assert_int_eq(is_valid, S21_FALSE);
}
END_TEST

Suite *make_suite_s21_validate_matrix(void) {
  Suite *s = suite_create("s21_validate_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_regular_matrix_valid);
  tcase_add_test(tc, test_manually_created_matrix_valid);
  tcase_add_test(tc, test_false_if_rows_null);
  tcase_add_test(tc, test_false_if_rows_less_zero);
  tcase_add_test(tc, test_false_if_columns_null);
  tcase_add_test(tc, test_false_if_columns_less_zero);
  tcase_add_test(tc, test_false_if_submatrix_pointer_to_null);
  tcase_add_test(tc, test_false_if_matrix_pointer_to_null);

  return s;
}
