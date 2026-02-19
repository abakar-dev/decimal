#include "../s21_decimal_test.h"

START_TEST(s21_test1) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(3, ret);
}
END_TEST

START_TEST(s21_test2) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {{1, 0, 0, 0}};
  s21_decimal *resultDc = NULL;

  int ret = s21_div(firstDc, secondDc, resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test3) {
  s21_decimal firstDc = {{0, 0, 0, 123}};
  s21_decimal secondDc = {{1, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test4) {
  s21_decimal firstDc = {{0, 0, 0, 0}};
  s21_decimal secondDc = {{1, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test5) {
  s21_decimal firstDc = {{1, 0, 0, 123}};
  s21_decimal secondDc = {{1, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test6) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {{1, 0, 0, 0}};
  s21_decimal resultDc = {{0, 0, 0, 123}};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test7) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test8) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{2, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(2, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test9) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{2, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&firstDc);

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(1, get_sign(resultDc));
  ck_assert_int_eq(2, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test10) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{2, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&secondDc);

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(1, get_sign(resultDc));
  ck_assert_int_eq(2, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test11) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{2, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&firstDc);
  set_sign(&secondDc);

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(2, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test12) {
  s21_decimal firstDc = {{4, 0, 0, 0}};
  s21_decimal secondDc = {{0, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(3, ret);
}
END_TEST

START_TEST(s21_test13) {
  s21_decimal firstDc = {{1000, 0, 0, 0}};
  s21_decimal secondDc = {{20, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(0, get_scale(resultDc));

  ck_assert_int_eq(50, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test14) {
  s21_decimal firstDc = {{123, 0, 0, 0}};
  s21_decimal secondDc = {{3, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(0, get_scale(resultDc));

  ck_assert_int_eq(41, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test15) {
  s21_decimal firstDc = {{519, 0, 0, 0}};
  s21_decimal secondDc = {{4, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(2, get_scale(resultDc));

  ck_assert_int_eq(12975, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test16) {
  s21_decimal firstDc = {{51912, 0, 0, 0}};
  s21_decimal secondDc = {{4, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&firstDc, 2);

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(2, get_scale(resultDc));

  ck_assert_int_eq(12978, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test18) {
  s21_decimal firstDc = {{51912, 0, 0, 0}};
  s21_decimal secondDc = {{4, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&secondDc, 1);
  set_scale(&firstDc, 4);

  int ret = s21_div(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(3, get_scale(resultDc));

  ck_assert_int_eq(12978, resultDc.bits[0]);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s;
  TCase *s21_testing;

  s = suite_create("\033[32m div \033[0m");
  s21_testing = tcase_create("\033[31m div \033[0m");

  tcase_add_test(s21_testing, s21_test1);
  tcase_add_test(s21_testing, s21_test2);
  tcase_add_test(s21_testing, s21_test3);
  tcase_add_test(s21_testing, s21_test4);
  tcase_add_test(s21_testing, s21_test5);
  tcase_add_test(s21_testing, s21_test6);
  tcase_add_test(s21_testing, s21_test7);
  tcase_add_test(s21_testing, s21_test8);
  tcase_add_test(s21_testing, s21_test9);
  tcase_add_test(s21_testing, s21_test10);
  tcase_add_test(s21_testing, s21_test11);
  tcase_add_test(s21_testing, s21_test12);
  tcase_add_test(s21_testing, s21_test13);
  tcase_add_test(s21_testing, s21_test14);
  tcase_add_test(s21_testing, s21_test15);
  tcase_add_test(s21_testing, s21_test16);
  tcase_add_test(s21_testing, s21_test18);

  suite_add_tcase(s, s21_testing);

  return s;
}
