#include <check.h>

#include "../s21_matrix.h"

static matrix_t A;
static matrix_t result;
static matrix_t expected;
static int is_equal;
static int status;

static void setup(void) {
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 1, &expected);
  is_equal = -99;
  status = -99;
}

static void teardown(void) {
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}

START_TEST(test_empty_same_size_matrix_return_empty_matrix) {
  status = s21_mult_number(&A, 0.99, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_mult_all_rows_and_columns) {
  A.matrix[0][0] = 256.0, A.matrix[1][0] = 1;
  expected.matrix[0][0] = 512.0, expected.matrix[1][0] = 2.0;

  status = s21_mult_number(&A, 2.0, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_first_bad) {
  A.rows = 0;  // Makes matrix incorrect

  status = s21_mult_number(&A, 5.0, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_result_null_pointer) {
  matrix_t *null_ptr = NULL;

  status = s21_mult_number(&A, 33.0, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

Suite *make_suite_s21_mult_number(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_empty_same_size_matrix_return_empty_matrix);
  tcase_add_test(tc, test_mult_all_rows_and_columns);
  tcase_add_test(tc, test_return_bad_matrix_if_first_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_result_null_pointer);

  return s;
}
