#include "s21_decimal.h"

s21_decimal div_logic(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *remainder);
int dagree_find(s21_decimal value_1, s21_decimal value_2);
int scale_logic(s21_decimal *value_1, s21_decimal *value_2,
                s21_decimal *result) {
  int errorFlag = 0;
  int var = get_scale(*value_1) - get_scale(*value_2);

  if (var > 0) {
    s21_decimal mldc = {{pow(10, var), 0, 0, 0}};
    set_scale(value_2, 0);
    errorFlag |= s21_mul(*value_2, mldc, value_2);
    set_scale(value_2, get_scale(*value_1));
    set_scale(result, get_scale(*value_1));
  } else if (var < 0) {
    s21_decimal mldc = {{pow(10, abs(var)), 0, 0, 0}};
    set_scale(value_1, 0);
    errorFlag |= s21_mul(*value_1, mldc, value_1);
    set_scale(value_1, get_scale(*value_2));
    set_scale(result, get_scale(*value_1));
  } else {
    set_scale(result, get_scale(*value_1));
  }

  return errorFlag;
}

int add_logic(s21_decimal *result, int bitsPart, int bit, int bitsSumm) {
  int errorFlag = 0;

  if (bitsSumm == 0 || bitsSumm == 1) {
    set_bit(&result->bits[bitsPart], bit, bitsSumm);
  } else {  // 2 || 3
    set_bit(&result->bits[bitsPart], bit, bitsSumm - 2);
    if (bit + 1 == 32) {
      if (bitsPart + 1 < 3)
        set_bit(&result->bits[bitsPart + 1], 0, 1);
      else
        errorFlag |= 1;
    } else
      set_bit(&result->bits[bitsPart], bit + 1, 1);
  }

  return errorFlag;
}
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int errorFlag = 0;
  if (correct_decimal_check(value_1, value_2, result)) return 4;

  decimal_init(result);
  // errorFlag |= scale_logic(&value_1, &value_2, result);

  if (get_sign(value_1) || get_sign(value_2)) {
    if (get_sign(value_2)) {
      set_sign(&value_2);
      errorFlag |= s21_sub(value_1, value_2, result);
    } else {
      set_sign(&value_1);
      errorFlag |= s21_sub(value_2, value_1, result);
    }

  } else {
    errorFlag = scale_logic(&value_1, &value_2, result);
    for (int bitsPart = 0; bitsPart < 3; bitsPart++) {
      for (int bit = 0; bit < 32; bit++) {
        int bitsSumm = get_bit(value_1.bits[bitsPart], bit) +
                       get_bit(value_2.bits[bitsPart], bit) +
                       get_bit(result->bits[bitsPart], bit);
        errorFlag |= add_logic(result, bitsPart, bit, bitsSumm);
      }
    }
  }

  return (errorFlag && get_sign(*result)) ? 2 : errorFlag;
}

void sub_borrow_logic(s21_decimal *value_1, int bitsPart, int bit) {
  while (bitsPart < 3) {
    if (bit > 31) {
      bitsPart += 1;
      bit = 0;
    }

    if (get_bit(value_1->bits[bitsPart], bit) == 0) {
      set_bit(&value_1->bits[bitsPart], bit, 1);
    } else {
      set_bit(&value_1->bits[bitsPart], bit, 0);
      break;
    }
    bit++;
  }
}
void choose_sub_method(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result) {
  for (int bitsPart = 0; bitsPart < 3; bitsPart++) {
    for (int bit = 0; bit < 32; bit++) {
      int value_1_bit = get_bit(value_1.bits[bitsPart], bit);
      int value_2_bit = get_bit(value_2.bits[bitsPart], bit);

      if (value_1_bit > value_2_bit)
        set_bit(&result->bits[bitsPart], bit, 1);
      else if (value_1_bit == value_2_bit)
        set_bit(&result->bits[bitsPart], bit, 0);
      else if (value_1_bit < value_2_bit) {
        set_bit(&result->bits[bitsPart], bit, 1);
        sub_borrow_logic(&value_1, bitsPart, bit + 1);
      }
    }
  }
}
void turn_over(s21_decimal *value_1, s21_decimal *value_2,
               s21_decimal *result) {
  if (decimal_mantissa_less(*value_1, *value_2)) {
    s21_decimal var = *value_2;
    *value_2 = *value_1;
    *value_1 = var;
    set_sign(result);
  }
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int errorFlag = 0;
  if (correct_decimal_check(value_1, value_2, result)) return 4;

  decimal_init(result);

  if (get_sign(value_1) || get_sign(value_2)) {
    if (get_sign(value_2)) {
      set_sign(&value_2);
      errorFlag |= s21_add(value_1, value_2, result);
    } else {
      set_sign(&value_1);
      errorFlag |= s21_add(value_2, value_1, result);
      set_sign(result);
    }

  } else {
    errorFlag |= scale_logic(&value_1, &value_2, result);
    turn_over(&value_1, &value_2, result);
    choose_sub_method(value_1, value_2, result);
  }

  return (errorFlag && get_sign(*result)) ? 2 : errorFlag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
  int status = 0;
  int result_sign = 5;

  if (get_sign(value_1) != get_sign(value_2)) {
    result_sign = 1;
  } else {
    result_sign = 0;
  }

  set_sign(&value_1);
  set_sign(&value_2);

  int last_bit = getBitLast(value_1);

  for (int bit_index = 0; bit_index <= last_bit; bit_index++) {
    s21_decimal partial_result = {{0, 0, 0, 0}};
    int current_bit_value = getBit(value_1, bit_index);

    if (current_bit_value) {
      partial_result = value_2;
      leftShift(&partial_result, bit_index);
      status = addBit(*result, partial_result, result);
    }
  }

  if (status) {
    while (get_scale(value_1) > 0 || get_scale(value_2) > 0) {
      s21_decimal *primary_value, *secondary_value;
      if (getBitLast(value_1) > getBitLast(value_2) && get_scale(value_1) > 0) {
        primary_value = &value_1;
        secondary_value = &value_2;
      } else if (getBitLast(value_2) > getBitLast(value_1) &&
                 get_scale(value_2) > 0) {
        primary_value = &value_2;
        secondary_value = &value_1;
      } else {
        break;
      }
      int scale_val = get_scale(*primary_value);
      decreaseScale(primary_value, 1);
      set_scale(primary_value, --scale_val);
      return s21_mul(*primary_value, *secondary_value, result);
    }
  }

  int total_scale = get_scale(value_1) + get_scale(value_2);
  set_scale(result, total_scale);
  set_scale(result, result_sign);

  if (status && result_sign) status = 2;

  return status;
}

int div_scale_logic(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  int errorFlag = 0;

  int resScale = get_scale(value_1) - get_scale(value_2);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);

  s21_decimal quotient = {0};
  s21_decimal remainder = value_1;
  s21_decimal ten = {{10, 0, 0, 0}};

  do {
    quotient = div_logic(value_1, value_2, &remainder);
    s21_add(*result, quotient, result);
    if (!decimal_null_check(remainder)) {
      s21_decimal temp = *result;
      errorFlag |= s21_mul(temp, ten, &temp);

      errorFlag |= s21_mul(remainder, ten, &value_1);
      if (errorFlag == 0 && resScale + 1 != 29) {
        *result = temp;
        resScale++;
      } else {
        break;
      }
    }
  } while (!decimal_null_check(remainder) && errorFlag == 0);

  if (resScale < 0) return 2;
  set_scale(result, resScale);

  return errorFlag;
}
s21_decimal div_logic(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *remainder) {
  s21_decimal quotient = {0};
  *remainder = value_1;

  int dagree = dagree_find(value_1, value_2);
  for (int j = dagree; j >= 0; j--) {
    s21_decimal v2Copy = value_2;
    decimal_bit_left_shift(v2Copy, &v2Copy, j);
    if (decimal_mantissa_less(v2Copy, *remainder) ||
        decimal_mantissa_equal(v2Copy, *remainder)) {
      s21_sub(*remainder, v2Copy, remainder);
      s21_decimal shiftDec = {{1, 0, 0, 0}};
      decimal_bit_left_shift(shiftDec, &shiftDec, j);
      s21_add(quotient, shiftDec, &quotient);
    }
  }

  return quotient;
}
int dagree_find(s21_decimal value_1, s21_decimal value_2) {
  int errorFlag = 0;
  int i = 0;
  for (i = 0; decimal_mantissa_less(value_2, value_1) ||
              decimal_mantissa_equal(value_2, value_1);
       i++) {
    errorFlag = decimal_bit_left_shift(value_2, &value_2, 1);
    if (errorFlag) {
      break;
    }
  }

  return i - 1;
}
int div_sign_logic(s21_decimal *value_1, s21_decimal *value_2) {
  int is_minus = 0;
  if (get_sign(*value_1) != get_sign(*value_2)) {
    (get_sign(*value_1)) ? set_sign(value_1) : set_sign(value_2);
    is_minus = 1;
  } else if (get_sign(*value_1)) {
    set_sign(value_1);
    set_sign(value_2);
  }
  return is_minus;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int errorFlag = 0;
  if (decimal_null_check(value_2)) return 3;
  if (correct_decimal_check(value_1, value_2, result)) return 4;

  decimal_init(result);
  int is_minus = div_sign_logic(&value_1, &value_2);

  //*result = div_logic(value_1, value_2, &value_2);
  errorFlag = div_scale_logic(value_1, value_2, result);

  if (is_minus) set_sign(result);

  return errorFlag;
}
