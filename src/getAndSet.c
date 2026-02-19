#include "s21_decimal.h"

int get_bit(int value, int pos) {
  int result = 0;
  for (int i = 31; i >= 0; i--) {
    if (i == pos) {
      (value & (1 << i)) ? (result = 1) : (result = 0);
    }
  }
  return result;
}
int get_sign(s21_decimal value) { return get_bit(value.bits[3], 31); }
int get_scale(s21_decimal value) {
  int scale = 0;

  for (int i = 16, j = 0; i <= 23; i++, j++) {
    set_bit(&scale, j, get_bit(value.bits[3], i));
  }

  return scale;
}

int set_bit(int* value, int pos, int bit) {
  int errorReturn = 0;
  if (bit != 0 && bit != 1) {
    fprintf(stderr, "Error :: cannot set non-binary value\n");
    errorReturn = 1;
  }
  for (int i = 31; i >= 0 && errorReturn == 0; i--) {
    if (i == pos) {
      if (get_bit(*value, pos) == 0 && bit == 1)
        *value = *value | (1 << i);
      else if (get_bit(*value, pos) != 0 && bit == 0)
        *value = *value ^ (1 << i);
    }
  }

  return errorReturn;
}
int set_sign(s21_decimal* value) {
  set_bit(&value->bits[3], 31, !get_bit(value->bits[3], 31));
  return get_bit(value->bits[3], 31);
}
int set_scale(s21_decimal* value, int scale) {
  int errorFlag = 0;
  if (scale >= 0 && scale <= 28) {
    for (int i = 16, j = 0; i <= 23; i++, j++) {
      set_bit(value->bits + 3, i, get_bit(scale, j));
    }
  } else
    errorFlag = 1;

  return errorFlag;
}