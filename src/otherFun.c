#include "s21_decimal.h"

int correct_decimal_check(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  int flag = 0;
  flag |= check_corrrect_decimal(value_1);
  flag |= check_corrrect_decimal(value_2);
  if (result == NULL) flag = 1;

  return flag;
}

void decimal_init(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

int decimal_mantissa_less(s21_decimal value_1, s21_decimal value_2) {
  for (int bitPart = 2; bitPart >= 0; bitPart--) {
    for (int bit = 31; bit >= 0; bit--) {
      if (get_bit(value_1.bits[bitPart], bit) <
          get_bit(value_2.bits[bitPart], bit))
        return 1;
      else if (get_bit(value_1.bits[bitPart], bit) >
               get_bit(value_2.bits[bitPart], bit))
        return 0;
    }
  }
  return 0;
}
int decimal_mantissa_equal(s21_decimal value_1, s21_decimal value_2) {
  return (value_1.bits[0] == value_2.bits[0] &&
          value_1.bits[1] == value_2.bits[1] &&
          value_1.bits[2] == value_2.bits[2]);
}

int shift_result_write(s21_decimal *result, int bitsPart, int shift) {
  int errorFlag = 0;

  int newBitPart = bitsPart + shift / 32;
  int newBit = shift % 32;

  if (newBitPart < 3) {
    set_bit(&result->bits[newBitPart], newBit, 1);
  } else {
    errorFlag = 1;
  }

  return errorFlag;
}
int decimal_bit_left_shift(s21_decimal value, s21_decimal *result, int shift) {
  int errorFlag = 0;

  decimal_init(result);

  for (int bitsPart = 0; bitsPart < 3; bitsPart++) {
    for (int bit = 0; bit < 32; bit++) {
      if (get_bit(value.bits[bitsPart], bit) == 1) {
        errorFlag |= shift_result_write(result, bitsPart, bit + shift);
      }
    }
  }

  return errorFlag;
}

int getBit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}
s21_decimal *setBit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}
int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int final_result = 0, carry = 0;

  for (int bit_idx = 0; bit_idx < 96; bit_idx++) {
    int bit_val1 = getBit(value_1, bit_idx);
    int bit_val2 = getBit(value_2, bit_idx);

    if (!bit_val1 && !bit_val2) {
      carry ? setBit(result, bit_idx, (carry = 0) + 1)
            : setBit(result, bit_idx, 0);
    } else if (bit_val1 != bit_val2) {
      carry ? setBit(result, bit_idx, (carry = 1) - 1)
            : setBit(result, bit_idx, 1);
    } else {
      carry ? setBit(result, bit_idx, (carry = 1))
            : setBit(result, bit_idx, (carry = 1) - 1);
    }

    if (bit_idx == 95 && carry == 1 && !getBit(value_1, 97) &&
        !getBit(value_2, 97)) {
      final_result = 1;
    }
  }

  return final_result;
}
int getBitLast(s21_decimal value) {
  int bitLast = 95;
  for (; (bitLast >= 0) && (!getBit(value, bitLast));) bitLast -= 1;
  return bitLast;
}
s21_decimal *leftShift(s21_decimal *value, int shift) {
  if (!(getBitLast(*value) + shift > 95)) {
    for (int shift_idx = 0; shift_idx < shift; shift_idx++) {
      int bit_shift_31 = getBit(*value, 31);
      int bit_shift_63 = getBit(*value, 63);

      for (int bit_idx = 0; bit_idx < 3; bit_idx++) {
        value->bits[bit_idx] <<= 1;
      }

      if (bit_shift_31) setBit(value, 32, 1);
      if (bit_shift_63) setBit(value, 64, 1);
    }
  }
  return value;
}
s21_decimal *decreaseScale(s21_decimal *value, int shift) {
  for (int shift_count = 0; shift_count < shift; shift_count++) {
    unsigned long long temp_overflow = value->bits[2];
    for (int bit_index = 2; bit_index >= 0; bit_index--) {
      value->bits[bit_index] = temp_overflow / 10;
      temp_overflow =
          (temp_overflow % 10) * ((unsigned long long)4294967295 + 1) +
          value->bits[bit_index > 0 ? bit_index - 1 : bit_index];
    }
  }

  set_scale(value, get_scale(*value) - shift);
  return value;
}