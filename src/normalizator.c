#include "decimal.h"

void normalizator(decimal *value1, decimal *value2) {
  decimal a = *value1;
  decimal b = *value2;
  decimal ten = {{10, 0, 0, 0}};
  decimal res = {{0, 0, 0, 0}};
  decimal mod = {{0, 0, 0, 0}};
  a = check_minus_null(a);
  b = check_minus_null(b);
  int znak_a = get_sign(a);
  int znak_b = get_sign(b);
  int scale_1 = get_scale(*value1);
  int scale_2 = get_scale(*value2);
  int raznica_stepen = 0;

  if (scale_1 < scale_2) {
    if (1 < (raznica_stepen = scale_2 - scale_1))
      for (int i = 0; i < raznica_stepen - 1; i++) mult_by_10(ten, &ten);

    if (!multiplication(a, ten, &res)) {
      set_scale(&res, scale_1 + raznica_stepen);
      a = res;
    } else {
      division(b, ten, &b, &mod, ROUND);
      set_scale(&b, scale_2 - raznica_stepen);
    }
    *value1 = a;
    *value2 = b;
    set_bit(value1, 127, znak_a);
    set_bit(value2, 127, znak_b);
  } else if (scale_1 > scale_2)
    normalizator(value2, value1);
}

int left_shift(decimal *value, int shift) {
  int flag = 0;
  for (int i = 95; 95 - shift < i; i--)
    if (get_bit(*value, i)) flag = 1;
  if (!flag)
    for (int i = 95; i >= 0; i--)
      set_bit(value, i, shift <= i ? get_bit(*value, i - shift) : 0);
  return flag;
}

void right_shift(decimal *value, int shift) {
  for (int i = 0; i < 96 && 0 < shift; i++) {
    if (i < 96 - shift) set_bit(value, i, get_bit(*value, i + shift));
    if (95 - shift < i) set_bit(value, i, 0);
  }
}

int addition(decimal value1, decimal value2, decimal *result) {
  decimal a = value1, b = value2;
  int temp = 0, overflow = RES_OK;
  for (int i = 0; i < 96; i++) {
    int sum_bits = get_bit(a, i) + get_bit(b, i) + temp;
    if (sum_bits == 0) {
      set_bit(result, i, 0);
      temp = 0;
    } else if (sum_bits == 1) {
      set_bit(result, i, 1);
      temp = 0;
    } else if (sum_bits == 2) {
      set_bit(result, i, 0);
      temp = 1;
    } else if (sum_bits == 3) {
      set_bit(result, i, 1);
      temp = 1;
    }
    if (i == 95 && temp != 0) overflow = RES_OVERFLOW;
  }

  int first_bit1 = position_of_first_bit(&value1);
  int first_bit2 = position_of_first_bit(&value2);
  int first_bit_res = position_of_first_bit(result);

  if (first_bit1 > first_bit_res || first_bit2 > first_bit_res ||
      (get_sign(value1) == 0 && first_bit1 == 95 && first_bit2 == 95)) {
    if (get_sign(value1)) {
      memset(result, 0, sizeof(decimal));
      delete_scale(result);
      overflow = RES_MIN_OVERFLOW;  // знак - и число слишком мало
    } else {
      memset(result, 0, sizeof(decimal));
      delete_scale(result);
      overflow = RES_OVERFLOW;  // знак + и число слишком велико
    }
  }
  return overflow;
}

int mult_by_10(decimal ten, decimal *ten_res) {
  decimal temp1 = ten, temp2 = ten;
  int error = left_shift(&temp1, 3);
  error |= left_shift(&temp2, 1);
  error |= addition(temp1, temp2, ten_res);
  if (error) *ten_res = ten;
  return error;
}

void div_by_ten(decimal *value) {
  long initial = 0;
  int rest = 0;
  for (int i = 2; i >= 0; i--) {
    initial = rest * 4294967296 + value->bits[i];
    value->bits[i] = initial / 10;
    rest = initial - value->bits[i] * 10;
  }
}

int comparison_mantissa(decimal value1, decimal value2) {
  int temp = 0;
  int res = EQUAL;
  for (int i = 0; i < 3; i++) temp |= value1.bits[i] ^ value2.bits[i];
  if (temp)
    for (int j = 2; j > -1; j--) {
      if (value1.bits[j] > value2.bits[j]) {
        res = MORE;
        j = -1;
      } else if (value1.bits[j] < value2.bits[j]) {
        res = LESS;
        j = -1;
      }
    }
  return res;
}

int multiplication(decimal value1, decimal value2, decimal *res) {
  decimal a = value1, b = value2, temp = {{0, 0, 0, 0}};
  int err = RES_OK;
  for (int i = 0; i < 96; i++)
    if (get_bit(a, i)) {
      b = value2;
      if (left_shift(&b, i))
        err = RES_OVERFLOW;
      else if (addition(b, temp, &temp))
        err = RES_OVERFLOW;
    }
  *res = temp;
  return err;
}

// возвращает разницу между битами, насколько нужно шифтить
int count_of_shift(decimal value1, decimal value2, decimal *res) {
  int bits1 = 95, bits2 = 95;
  for (; !get_bit(value1, bits1) && 0 < bits1;) bits1--;
  for (; !get_bit(value2, bits2) && 0 < bits2;) bits2--;
  decimal temp = value2;
  left_shift(&temp, bits1 - bits2);
  if (comparison_mantissa(temp, value2) == MORE) {
    right_shift(&temp, 1);
    bits1--;
  }
  *res = temp;
  return bits1 - bits2;
}

void substraction(decimal value1, decimal value2, decimal *res) {
  decimal tmp = value1;
  decimal a = value2;
  for (int i = 0; i < 96; i++) {
    int sum_bits = get_bit(tmp, i) - get_bit(a, i);
    if (sum_bits == 0)
      set_bit(res, i, 0);
    else if (sum_bits == 1)
      set_bit(res, i, 1);
    else if (sum_bits == -1) {
      set_bit(res, i, 1);
      int j = i;
      for (; !get_bit(tmp, j); j++) set_bit(&tmp, j, 1);
      set_bit(&tmp, j, 0);
    }
  }
}

int division(decimal value1, decimal value2, decimal *res,
             decimal *mod, int round) {
  decimal a = value1;
  decimal b = value2;
  decimal mod2 = {{0, 0, 0, 0}};
  declare_to_null(res);
  int i = 0;
  int error = RES_OK;
  int null = !comparison_mantissa(value2, mod2);
  if (null) error = RES_MIN_OVERFLOW;
  if (!error && comparison_mantissa(b, a) == 1)
    *mod = a;
  else {
    while (comparison_mantissa(a, b) != LESS && !error) {
      decimal c = {{0, 0, 0, 0}};
      decimal temp = {{1, 0, 0, 0}};
      i = count_of_shift(a, b, &c);
      error = left_shift(&temp, i);
      error = addition(*res, temp, res);
      substraction(a, c, mod);
      a = *mod;
    }
    if (round != ROUND_MOD && !error) a = round_div_mantissa(a, b, res, round);
  }
  if (error) declare_to_null(res);
  return error;
}

decimal round_div_mantissa(decimal a, decimal b, decimal *res,
                               int round) {
  decimal ostatok_c = a;
  decimal res_r = {{0, 0, 0, 0}};
  decimal ostatok = {{2, 0, 0, 0}};
  decimal nul = {{0, 0, 0, 0}};
  decimal mod = {{0, 0, 0, 0}};
  left_shift(&ostatok_c, 1);
  if (round == ROUND) {
    division(ostatok_c, b, &res_r, &mod, NO_ROUND);
    addition(*res, res_r, res);
  } else if (round == ROUND_B) {
    division(ostatok_c, ostatok, &res_r, &ostatok, NO_ROUND);
    if (comparison_mantissa(nul, ostatok) != EQUAL) {
      division(ostatok_c, b, &res_r, &mod, NO_ROUND);
      addition(*res, res_r, res);
    }
  }
  return nul;
}

decimal check_minus_null(decimal value) {
  decimal null = {{0, 0, 0, get_scale(value) << 16}};
  decimal temp = value;

  if (comparison_mantissa(temp, null) == 0 && get_bit(temp, 127)) {
    return null;
  } else {
    return temp;
  }
}
