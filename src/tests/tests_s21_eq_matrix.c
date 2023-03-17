#include <check.h>

#include "../s21_matrix.h"

static matrix_t A;
static matrix_t B;
static int is_equal;

static void setup(void) {
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 1, &B);
  is_equal = -99;
}

static void teardown(void) {
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_empty_same_size_matrix_equal) {
  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_not_equal_if_first_matrix_pointer_to_null) {
  is_equal = s21_eq_matrix(&A, NULL);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_not_equal_if_second_matrix_pointer_to_null) {
  is_equal = s21_eq_matrix(&A, NULL);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_not_equal_if_first_matrix_not_valid) {
  A.rows = 0;  // Make A matrix invalid

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_not_equal_if_second_matrix_not_valid) {
  B.columns = 0;  // Make A matrix invalid

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_not_equal_if_rows_count_differs) {
  B.rows = 1;  // A matrix has 2 rows

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_not_equal_if_columns_count_differs) {
  A.columns = 2;  // B matrix has 1 columns

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

START_TEST(test_equal_if_values_differs_but_less_epsilon) {
  A.matrix[1][0] = 2.000000002;
  B.matrix[1][0] = 2.0000000002;

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_not_equal_if_values_differs_more_than_epsilon) {
  A.matrix[1][0] = 2.000002;
  B.matrix[1][0] = 2.000004;

  is_equal = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(is_equal, FAILURE);
}
END_TEST

Suite *make_suite_s21_eq_matrix(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_empty_same_size_matrix_equal);
  tcase_add_test(tc, test_not_equal_if_first_matrix_pointer_to_null);
  tcase_add_test(tc, test_not_equal_if_second_matrix_pointer_to_null);
  tcase_add_test(tc, test_not_equal_if_first_matrix_not_valid);
  tcase_add_test(tc, test_not_equal_if_second_matrix_not_valid);
  tcase_add_test(tc, test_not_equal_if_rows_count_differs);
  tcase_add_test(tc, test_not_equal_if_columns_count_differs);
  tcase_add_test(tc, test_equal_if_values_differs_but_less_epsilon);
  tcase_add_test(tc, test_not_equal_if_values_differs_more_than_epsilon);

  return s;
}
