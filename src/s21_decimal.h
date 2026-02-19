#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int bits[4];
} s21_decimal;

int check_corrrect_decimal(s21_decimal value);
int decimal_null_check(s21_decimal value);
int correct_decimal_check(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);

void decimal_init(s21_decimal *value);
int decimal_mantissa_greater(s21_decimal value_1, s21_decimal value_2);
int decimal_mantissa_less(s21_decimal value_1, s21_decimal value_2);
int decimal_mantissa_equal(s21_decimal value_1, s21_decimal value_2);
int decimal_bit_left_shift(s21_decimal value, s21_decimal *result, int shift);

int get_bit(int value, int pos);
int get_sign(s21_decimal value);
int get_scale(s21_decimal value);
int set_bit(int *value, int pos, int bit);
int set_sign(s21_decimal *value);
int set_scale(s21_decimal *value, int scale);

int getBit(s21_decimal value, int bit);
s21_decimal *setBit(s21_decimal *value, int pos, int bit);
int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int getBitLast(s21_decimal value);
s21_decimal *leftShift(s21_decimal *value, int shift);
s21_decimal *decreaseScale(s21_decimal *value, int shift);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int compare_magnitude(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif