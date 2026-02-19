#include "s21_decimal.h"

int check_fourPart_emptData(s21_decimal value) {
  int errorFlag = 0;

  for (int i = 0; i < 32; i++) {
    if ((i >= 0 && i <= 15) || (i >= 24 && i <= 30)) {
      if (value.bits[3] & (1 << i)) {
        errorFlag = 1;
        break;
      }
    }
  }

  return errorFlag;
}
int check_scale(s21_decimal value) {
  return (get_scale(value) >= 0 && get_scale(value) <= 28) ? 0 : 1;
}
int check_corrrect_decimal(s21_decimal value) {
  return (check_fourPart_emptData(value) || check_scale(value)) ? 1 : 0;
}

int decimal_null_check(s21_decimal value) {
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) return 1;
  return 0;
}