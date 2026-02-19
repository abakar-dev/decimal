#include "s21_decimal.h"

int compare_magnitude(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 2; i >= 0; i--) {
    if (value_1.bits[i] > value_2.bits[i]) return 1;
    if (value_1.bits[i] < value_2.bits[i]) return -1;
  }
  return 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) return 0;
  }
  if (get_sign(value_1) != get_sign(value_2)) {
    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
      return 1;
    }
    return 0;
  }
  if (get_scale(value_1) != get_scale(value_2)) {
    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
      return 1;
    }
    return 0;
  }
  return 1;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (decimal_null_check(value_1) == 1 && decimal_null_check(value_2) == 1)
    return 0;
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);

  if (sign1 != sign2) return sign1 > sign2;

  if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 &&
      value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    return 0;
  }

  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);

  if (scale1 > scale2) {
    for (int i = scale1; i > scale2; i--) {
      for (int j = 2; j >= 0; j--) {
        value_1.bits[j] /= 10;
      }
    }
  } else if (scale2 > scale1) {
    for (int i = scale2; i > scale1; i--) {
      for (int j = 2; j >= 0; j--) {
        value_2.bits[j] /= 10;
      }
    }
  }

  int comparison = compare_magnitude(value_1, value_2);
  return (comparison < 0) ^ sign1;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}