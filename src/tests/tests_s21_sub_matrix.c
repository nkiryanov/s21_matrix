#include <check.h>

#include "../s21_matrix.h"

static matrix_t A;
static matrix_t B;
static matrix_t result;
static matrix_t expected;
static int is_equal;
static int status;

static void setup(void) {
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 1, &B);
  s21_create_matrix(2, 1, &expected);
  is_equal = -99;
  status = -99;
}

static void teardown(void) {
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}

START_TEST(test_empty_same_size_matrix_return_empty_matrix) {
  status = s21_sub_matrix(&A, &B, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_subs_all_rows_and_columns) {
  A.matrix[0][0] = 256.0, A.matrix[1][0] = 1;
  B.matrix[0][0] = 1, B.matrix[1][0] = 2;
  expected.matrix[0][0] = 255, expected.matrix[1][0] = -1;

  status = s21_sub_matrix(&A, &B, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_first_bad) {
  A.rows = 0;  // Makes matrix incorrect

  status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_second_bad) {
  B.columns = 0;  // Makes matrix incorrect

  status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_bad_matrix_if_result_null_pointer) {
  matrix_t *null_ptr = NULL;

  status = s21_sub_matrix(&A, &B, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_calculation_error_if_rows_differs) {
  A.rows = 10;  // B has only 2 rows

  status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calculation_error_if_columns_differs) {
  B.columns = 10;  // A has only 1 column

  status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *make_suite_s21_sub_matrix(void) {
  Suite *s = suite_create("s21_sub_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_empty_same_size_matrix_return_empty_matrix);
  tcase_add_test(tc, test_subs_all_rows_and_columns);
  tcase_add_test(tc, test_return_bad_matrix_if_first_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_second_bad);
  tcase_add_test(tc, test_return_bad_matrix_if_result_null_pointer);
  tcase_add_test(tc, test_return_calculation_error_if_rows_differs);
  tcase_add_test(tc, test_return_calculation_error_if_columns_differs);

  return s;
}
