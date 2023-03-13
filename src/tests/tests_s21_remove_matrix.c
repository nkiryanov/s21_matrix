#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;

static void setup(void) {
  matrix.rows = -99;
  matrix.columns = -99;
  matrix.matrix = NULL;
}

START_TEST(test_remove_matrix_set_everything_to_null) {
  s21_create_matrix(10, 11, &matrix);

  s21_remove_matrix(&matrix);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(test_do_not_fail_if_matrix_null) {
  int status = OK;

  s21_remove_matrix(NULL);

  // We test nothing here because our fuction return void
  // Just hope that valgrind or address sanitizer will find errors here
  // if we made it
  ck_assert_int_eq(status, OK);
}
END_TEST

Suite *make_suite_s21_remove_matrix(void) {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, NULL);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_remove_matrix_set_everything_to_null);
  tcase_add_test(tc, test_do_not_fail_if_matrix_null);

  return s;
}
