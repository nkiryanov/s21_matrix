#include <check.h>

#include "../s21_matrix.h"

static matrix_t matrix;
static matrix_t result;
static matrix_t expected;
static int is_equal;
static int status;

static void setup(void) {
  s21_create_matrix(7, 7, &matrix);
  s21_create_matrix(7, 7, &expected);
  is_equal = -99;
  status = -99;
}

static void teardown(void) {
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}

static void fill_matrix(double **A, matrix_t *matrix, int size) {
  matrix->rows = size;
  matrix->columns = size;

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix->matrix[i][j] = *((double *)(A + i * size) + j);
    }
  }
}

START_TEST(test_regular_case) {
  double matrix_initial[3][3] = {
      {1., 2., 3.},
      {3., 2., 1.},
      {7., 5., 2.},
  };
  double matrix_expected[3][3] = {
      {-0.25, 2.75, -1.},
      {0.25, -4.75, 2.},
      {0.25, 2.25, -1.},
  };
  fill_matrix((double **)matrix_initial, &matrix, 3);
  fill_matrix((double **)matrix_expected, &expected, 3);

  status = s21_inverse_matrix(&matrix, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_regular_with_not_obvious_result) {
  double matrix_initial[4][4] = {
      {1.80377, 3.93870, 3.13429, 2.28155},
      {1.39307, 1.05586, 2.21357, 2.20440},
      {2.74323, 2.41325, 3.86805, 2.73013},
      {2.29065, 3.09765, 1.84139, 3.86339},
  };
  double matrix_expected[4][4] = {
      {-0.6892499107, -1.6362600080, 1.2909415507, 0.4284039249},
      {0.3588626362, -0.3777606089, -0.1150224313, 0.0848991764},
      {0.2706058939, 0.7498401502, -0.1659167199, -0.4704092234},
      {-0.0080477312, 0.9156520525, -0.5941100018, 0.1609714411},
  };
  fill_matrix((double **)matrix_initial, &matrix, 4);
  fill_matrix((double **)matrix_expected, &expected, 4);

  status = s21_inverse_matrix(&matrix, &result);

  is_equal = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(is_equal, SUCCESS);
}
END_TEST

START_TEST(test_return_bad_matrix_if_determinant_zero) {
  double matrix_initial[4][4] = {
      {1.80377, 3.93870, 3.13429, 2.28155},
      {1.39307, 1.05586, 2.21357, 2.20440},
      {2.74323, 2.41325, 3.86805, 2.73013},
      {2.74323, 2.41325, 3.86805, 2.73013},
  };
  fill_matrix((double **)matrix_initial, &matrix, 4);

  status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_return_bad_matrix_if_matrix_bad) {
  matrix.rows = 0;  // Makes matrix incorrect

  status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_inverse_return_bad_matrix_if_result_null_pointer) {
  matrix_t *null_ptr = NULL;

  status = s21_inverse_matrix(&matrix, null_ptr);

  ck_assert_int_eq(status, BAD_MATRIX);
}
END_TEST

START_TEST(test_return_calculation_error_if_not_square) {
  matrix.rows = 1;  // Makes not square (there are 7 columns)

  status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *make_suite_s21_inverse_matrix(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, setup, teardown);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_regular_case);
  tcase_add_test(tc, test_regular_with_not_obvious_result);
  tcase_add_test(tc, test_return_bad_matrix_if_determinant_zero);
  tcase_add_test(tc, test_return_bad_matrix_if_matrix_bad);
  tcase_add_test(tc, test_inverse_return_bad_matrix_if_result_null_pointer);
  tcase_add_test(tc, test_return_calculation_error_if_not_square);

  return s;
}
