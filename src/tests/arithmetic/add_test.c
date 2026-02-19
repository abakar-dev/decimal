#include "../s21_decimal_test.h"

START_TEST(s21_test1) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test2) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal *resultDc = NULL;

  int ret = s21_add(firstDc, secondDc, resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test3) {
  s21_decimal firstDc = {{0, 0, 0, 123}};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test4) {
  s21_decimal firstDc = {{0, 0, 0, 0}};
  s21_decimal secondDc = {{0, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test5) {
  s21_decimal firstDc = {{0, 0, 0, 123}};
  s21_decimal secondDc = {{0, 0, 0, 123}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
}
END_TEST

START_TEST(s21_test6) {
  s21_decimal firstDc = {0};
  s21_decimal secondDc = {0};
  s21_decimal resultDc = {{0, 0, 0, 123}};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test7) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(s21_test8) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(12 + 8, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test9) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&firstDc);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(1, get_sign(resultDc));
  ck_assert_int_eq(4, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test10) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&secondDc);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(4, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test11) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{8, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_sign(&firstDc);
  set_sign(&secondDc);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(1, get_sign(resultDc));
  ck_assert_int_eq(20, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test18) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{10, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&firstDc, 1);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(1, get_scale(resultDc));
  ck_assert_int_eq(112, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test19) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&secondDc, 1);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(1, get_scale(resultDc));
  ck_assert_int_eq(135, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test20) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, 0);
}

START_TEST(s21_test21) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test22) {
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test23) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test24) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test25) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test26) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test27) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test28) {
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test29) {
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test30) {
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test31) {
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test32) {
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test33) {
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test34) {
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test35) {
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

START_TEST(s21_test36) {
  s21_decimal firstDc = {{12, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&firstDc, 1);
  set_scale(&secondDc, 1);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(1, get_scale(resultDc));
  ck_assert_int_eq(27, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test37) {
  s21_decimal firstDc = {{120390, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&firstDc, 4);
  set_scale(&secondDc, 1);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(4, get_scale(resultDc));
  ck_assert_int_eq(135390, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test38) {
  s21_decimal firstDc = {{120390, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0}};
  s21_decimal resultDc = {0};

  set_scale(&firstDc, 1);
  set_scale(&secondDc, 4);

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(4, get_scale(resultDc));
  ck_assert_int_eq(120390015, resultDc.bits[0]);
}
END_TEST

START_TEST(s21_test39) {
  s21_decimal firstDc = {{120390, 0, 0, 0b111010000000000000000}};
  s21_decimal secondDc = {{15, 0, 0, 0}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
}
END_TEST

START_TEST(s21_test40) {
  s21_decimal firstDc = {{120390, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0b111010000000000000000}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
}
END_TEST

START_TEST(s21_test41) {
  s21_decimal firstDc = {{120390, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0b00000000111111110000000000000000}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(4, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
}
END_TEST

START_TEST(s21_test42) {
  s21_decimal firstDc = {{120390, 0, 0, 0}};
  s21_decimal secondDc = {{15, 0, 0, 0b111000000000000000000}};
  s21_decimal resultDc = {0};

  int ret = s21_add(firstDc, secondDc, &resultDc);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(0, get_sign(resultDc));
  ck_assert_int_eq(28, get_scale(resultDc));
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s;
  TCase *s21_testing;

  s = suite_create("\033[32m add \033[0m");
  s21_testing = tcase_create("\033[31m add \033[0m");

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
  tcase_add_test(s21_testing, s21_test18);
  tcase_add_test(s21_testing, s21_test19);
  tcase_add_test(s21_testing, s21_test20);
  tcase_add_test(s21_testing, s21_test21);
  tcase_add_test(s21_testing, s21_test22);
  tcase_add_test(s21_testing, s21_test23);
  tcase_add_test(s21_testing, s21_test24);
  tcase_add_test(s21_testing, s21_test25);
  tcase_add_test(s21_testing, s21_test26);
  tcase_add_test(s21_testing, s21_test27);
  tcase_add_test(s21_testing, s21_test28);
  tcase_add_test(s21_testing, s21_test29);
  tcase_add_test(s21_testing, s21_test30);
  tcase_add_test(s21_testing, s21_test31);
  tcase_add_test(s21_testing, s21_test32);
  tcase_add_test(s21_testing, s21_test33);
  tcase_add_test(s21_testing, s21_test34);
  tcase_add_test(s21_testing, s21_test35);
  tcase_add_test(s21_testing, s21_test36);
  tcase_add_test(s21_testing, s21_test37);
  tcase_add_test(s21_testing, s21_test38);
  tcase_add_test(s21_testing, s21_test39);
  tcase_add_test(s21_testing, s21_test40);
  tcase_add_test(s21_testing, s21_test41);
  tcase_add_test(s21_testing, s21_test42);

  suite_add_tcase(s, s21_testing);

  return s;
}
