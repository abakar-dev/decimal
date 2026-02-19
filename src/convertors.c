#include <stdint.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src,
                            s21_decimal *dst) {  // Преобразование int в decimal
  if (dst == NULL) return 1;

  dst->bits[0] = (src >= 0) ? src : -src;
  dst->bits[1] = dst->bits[2] = 0;
  dst->bits[3] = (src < 0) ? 0x80000000 : 0;

  return 0;
}

typedef union {
  int ui;
  float fl;
} floayBits;
int ExpFloat(float *value) {
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}
static s21_decimal *setSign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}
int s21_from_float_to_decimal(float src, s21_decimal *dst) {  ////////////
  int res = 1, exp = ExpFloat(&src);
  if (dst && src != 0 && !isinf(src)) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      src *= -1;
      sign = 1;
    }
    double tmp = (double)src;
    int scale = 0;
    while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      scale++;
    }
    // tmp = round(tmp);
    if (scale <= 28 && (exp > -94 && exp < 96)) {
      floayBits mant;
      tmp = (float)tmp;
      for (; fmod(tmp, 10) == 0 && scale > 0; scale--, tmp /= 10) {
      }
      mant.fl = tmp;
      exp = ExpFloat(&mant.fl);
      setBit(dst, exp, 1);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mant.ui & (1 << j)) != 0) {
          setBit(dst, i, 1);
        }
      }
      setSign(dst, sign);
      set_scale(dst, scale);
      res = 0;
    }
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src,
                            int *dst) {  // преобразование decimal в int
  if (dst == NULL) return 1;

  *dst = src.bits[0];

  if (src.bits[3] & 0x80000000) *dst = -*dst;

  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 1;
  if (dst) {
    double tmp = 0;
    int exp = 0;
    for (int i = 0; i < 96; i++) {
      if ((src.bits[i / 32] & (1 << i % 32)) != 0) tmp += pow(2, i);
    }
    if ((exp = get_scale(src)) > 0) {
      for (int i = exp; i > 0; i--, tmp /= 10.0) {
      }
    }
    *dst = (float)tmp;
    if (get_sign(src)) {
      *dst *= -1;
    }
    res = 0;
  }
  return res;
}