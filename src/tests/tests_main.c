#include <check.h>
#include <stdlib.h>

#include "tests_suites.h"

int main(void) {
  int number_failed;
  SRunner *sr;
  sr = srunner_create(make_master_suite());

  srunner_add_suite(sr, make_suite_s21_create_matrix());
  srunner_add_suite(sr, make_suite_s21_eq_matrix());
  srunner_add_suite(sr, make_suite_s21_mult_matrix());
  srunner_add_suite(sr, make_suite_s21_mult_number());
  srunner_add_suite(sr, make_suite_s21_remove_matrix());
  srunner_add_suite(sr, make_suite_s21_sub_matrix());
  srunner_add_suite(sr, make_suite_s21_sum_matrix());
  srunner_add_suite(sr, make_suite_s21_validate_matrix());

  // We set NOFORK mode for debug ability and testing with valgrind
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
