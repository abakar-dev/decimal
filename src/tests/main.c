#include <stdlib.h>

#include "s21_decimal_test.h"

int test_logic(Suite *suite) {
  int test_result = 0;

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  test_result = srunner_ntests_failed(runner);

  srunner_free(runner);

  return test_result;
}

int main(int argc, char **argv) {
  int result;

  result = test_logic(s21_add_suite());
  result = test_logic(s21_sub_suite());
  result = test_logic(s21_mul_suite());
  result = test_logic(s21_div_suite());
  result = test_logic(s21_other_suite());

  return (result == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}