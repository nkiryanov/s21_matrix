#ifndef SRC_TESTS_TEST_SUITES_H_
#define SRC_TESTS_TEST_SUITES_H_

#include <check.h>

Suite *make_master_suite(void);
Suite *make_suite_s21_create_matrix(void);
Suite *make_suite_s21_eq_matrix(void);
Suite *make_suite_s21_mult_number(void);
Suite *make_suite_s21_remove_matrix(void);
Suite *make_suite_s21_sub_matrix(void);
Suite *make_suite_s21_sum_matrix(void);
Suite *make_suite_s21_validate_matrix(void);

#endif  // SRC_TESTS_TEST_SUITES_H_
