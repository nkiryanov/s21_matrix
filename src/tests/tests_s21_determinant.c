#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;
static double determinant;
static int status;

static void fill_matrix(double **A, matrix_t *matrix, int size) {
  matrix->rows = size;
  matrix->columns = size;

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix->matrix[i][j] = *((double *)(A + i * size) + j);
    }
  }
}

static void setup(void) {
  // We create 7 element square matrix but change size manually in `fill_matrix`
  s21_create_matrix(7, 7, &matrix);
  determinant = -99999;
  status = -99;
}

static void teardown(void) { s21_remove_matrix(&matrix); }

START_TEST(test_determinant_regular_case) {
  double matrix_values[4][4] = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16},
  };
  fill_matrix((double **)matrix_values, &matrix, 4);

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(determinant, 0.0, S21_EPSILON);
}
END_TEST

START_TEST(test_determinant_one_element_matrix) {
  double matrix_values[1] = {686.686595};
  fill_matrix((double **)matrix_values, &matrix, 1);

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(determinant, 686.686595, S21_EPSILON);
}
END_TEST

START_TEST(test_determinant_seven_sized_element_matrix) {
  double matrix_values[7][7] = {
      {3.54155, 2.53027, 2.52268, 3.32609, 1.74077, 1.84826, 2.31548},
      {1.79850, 1.03137, 3.21930, 2.23851, 3.69014, 1.86757, 2.58197},
      {3.12373, 2.50464, 2.81140, 3.95159, 3.93592, 2.55369, 2.85939},
      {2.53200, 2.17887, 3.89360, 2.57050, 1.35048, 2.86216, 2.85716},
      {2.45656, 2.44057, 3.60225, 2.02151, 2.66313, 3.54608, 1.99800},
      {2.73763, 3.62892, 3.16649, 1.46655, 1.63051, 3.30205, 1.16198},
      {2.99739, 1.10405, 3.75781, 1.69789, 2.66463, 2.54331, 1.13451},
  };
  fill_matrix((double **)matrix_values, &matrix, 7);

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(determinant, 24.111673073047285806, S21_EPSILON);
}
END_TEST

START_TEST(test_determinant_for_matrix_with_same_rows) {
  double matrix_values[3][3] = {
      {1., 2., 3.},
      {1., 2., 3.},
      {7., 8., 9.},
  };
  fill_matrix((double **)matrix_values, &matrix, 3);

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(determinant, 0.0, S21_EPSILON);
}
END_TEST

START_TEST(test_return_bad_matrix_if_matrix_bad) {
  matrix.rows = 0;  // Makes matrix incorrect

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_calculation_error_if_not_square) {
  matrix.columns = 3;  // Has 4 rows == not square

  status = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_calculation_error_if_result_null_ptr) {
  status = s21_determinant(&matrix, NULL);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *make_suite_s21_determinant(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_determinant_regular_case);
  tcase_add_test(tc, test_determinant_one_element_matrix);
  tcase_add_test(tc, test_determinant_seven_sized_element_matrix);
  tcase_add_test(tc, test_determinant_for_matrix_with_same_rows);
  tcase_add_test(tc, test_return_bad_matrix_if_matrix_bad);
  tcase_add_test(tc, test_return_calculation_error_if_not_square);
  tcase_add_test(tc, test_return_calculation_error_if_result_null_ptr);

  return s;
}
