#ifndef S21_DECIMAL_TEST
#define S21_DECIMAL_TEST

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"

Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);
Suite *s21_other_suite(void);

#endif