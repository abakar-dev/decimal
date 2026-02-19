#include "../s21_decimal_test.h"

START_TEST(s21_test1) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test3) {
  s21_decimal firstDc = {{0, 0, 0, 123}};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test4) {
  s21_decimal firstDc = {{0, 0, 0, 0}};
  s21_decimal secondDc = {{0, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test5) {
  s21_decimal firstDc = {{0, 0, 0, 123}};
  s21_decimal secondDc = {{0, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test6) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {{0, 0, 0, 123}};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test7) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test8) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{2, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_mul(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(8, resultDc.bits[0]);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s;
  TCase *s21_testing;

  s = suite_create("\033[32m mul \033[0m");
  s21_testing = tcase_create("\033[31m mul \033[0m");

  tcase_add_test(s21_testing, s21_test1);
  tcase_add_test(s21_testing, s21_test3);
  tcase_add_test(s21_testing, s21_test4);
  tcase_add_test(s21_testing, s21_test5);
  tcase_add_test(s21_testing, s21_test6);
  tcase_add_test(s21_testing, s21_test7);
  tcase_add_test(s21_testing, s21_test8);

  suite_add_tcase(s, s21_testing);

  return s;
}
