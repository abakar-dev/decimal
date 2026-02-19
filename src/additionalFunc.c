#include "s21_decimal.h"

s21_decimal* s21_reset(s21_decimal* value) {
  for (int x = 0; x < 4; x += 1) value->bits[x] = 0;
  return value;
}

s21_decimal s21_abs(s21_decimal value_1) {
  s21_decimal result = value_1;
  if (get_sign(result) == 1) set_sign(&result);
  return result;
}
int s21_floor(s21_decimal value, s21_decimal* result) {
  int errorFlag = 0;

  if (!result) {
    errorFlag = 1;
  } else if (check_corrrect_decimal(value)) {
    errorFlag = 1;
  } else {
    decimal_init(result);
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    s21_decimal value_unsigned = s21_abs(value);
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);

    s21_decimal nullDecimal = {{0}};
    if (sign == 1 && s21_is_greater(fractional, nullDecimal)) {
      s21_decimal oneDecimal = {{1, 0, 0, 0}};
      s21_add(value_unsigned_truncated, oneDecimal, &value_unsigned_truncated);
    }

    *result = value_unsigned_truncated;

    if (sign != get_sign(*result)) set_sign(result);
  }

  return errorFlag;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  int return_val = 0;
  decimal_init(result);
  float float_value = 0.0;
  s21_from_decimal_to_float(value, &float_value);
  float_value = roundf(float_value);
  if (float_value < 0.0) {
    set_sign(result);
    float_value *= -1;
  }
  for (int i = 0; float_value >= 1 && i < 96; i++) {
    float_value = floorl(float_value) / 2;
    if (float_value - floorl(float_value) > powl(10.0, -1 * 7)) {
      setBit(result, i, 1);
    }
  }
  set_scale(result, 0);
  return return_val;
}

s21_decimal* s21_copy(s21_decimal* dest, s21_decimal src) {
  for (int x = 0; x < 4; x += 1) dest->bits[x] = src.bits[x];
  return dest;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  int return_val = 0;
  decimal_init(result);
  if (!get_scale(value)) {
    s21_copy(result, value);
  } else {
    float float_value = 0.0;
    s21_from_decimal_to_float(value, &float_value);
    float_value = trunc(float_value);
    if (float_value < 0.0) {
      set_sign(result);
      float_value *= -1;
    }
    for (int i = 0; float_value >= 1 && i < 96; i++) {
      float_value = floorl(float_value) / 2;
      if (float_value - floorl(float_value) > powl(10.0, -1 * 7)) {
        setBit(result, i, 1);
      }
    }
    set_scale(result, 0);
  }
  return return_val;
}

s21_decimal* setSign(s21_decimal* value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  s21_copy(s21_reset(result),
           get_sign(value) ? *setSign(&value, 0) : *setSign(&value, 1));
  return 0;
}