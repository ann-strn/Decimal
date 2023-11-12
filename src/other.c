#include "decimal.h"

int truncate(decimal value, decimal *result) {
  int error = 0;
  *result = value;
  if (result == NULL) error = 1;

  int int_pow = 0;
  for (int i = 126; i >= 96 && !error; i--) {
    if ((i > 119 || i < 112) && get_bit(value, i)) {
      error = 1;
    } else if ((i < 120 && i > 111)) {
      int_pow += get_bit(value, i) * pow(2, i - 112);
      if (int_pow > 28) error = 1;
    }
  }  // pow + error check
  if (!error && int_pow) {
    for (int i = 119; i > 111; i--) {
      set_bit(result, i, 0);  // обнуление степени
    }
    for (int i = 0; i < int_pow; i++) {
      div_by_ten(result);
    }
  }
  return error;
}

int negate(decimal value, decimal *result) {
  *result = value;
  int error = 0;
  if (result == NULL) error = 1;

  for (int i = 126; i > 95 && !error; i--) {
    if ((i > 119 || (i < 112 && i > 95)) && get_bit(value, i)) {
      error = 1;
    }
  }
  if (!error) {
    set_bit(result, 127, !get_bit(value, 127));
  }
  return error;
}

int floor(decimal value, decimal *result) {
  int error = 0;
  int zero_value = 1;

  if (!result) return 1;
  for (int i = 95; i >= 0 && zero_value; i--) {
    if (get_bit(value, i)) zero_value = 0;
  }
  error = truncate(value, result);
  if (!error && !zero_value && get_bit(*result, 127) &&
      get_scale(value)) {  // result < 0
    int i = 0;
    while (get_bit(*result, i)) {
      set_bit(result, i, 0);
      i++;
    }
    set_bit(result, i, 1);
  }
  return error;
}

int round(decimal value, decimal *result) {
  int error = 0;
  int zero_value = 1;
  for (int i = 95; i >= 0 && zero_value; i--)
    if (get_bit(value, i)) zero_value = 0;

  error = truncate(value, result);  // result is int part
  if (!error && !zero_value && get_scale(value)) {
    decimal diff = {0};
    sub(value, *result, &diff);  // diff is floating part
    decimal zerohalf = {0};
    from_int_to_decimal(5, &zerohalf);
    set_scale(&zerohalf, 1);  // zerohalf is 0.5 decimal
    if (is_greater_or_equal(abs_dec(diff),
                                zerohalf)) {  // |difference| >= 0.5
      int i = 0;
      while (get_bit(*result, i)) {
        set_bit(result, i, 0);
        i++;
      }
      set_bit(result, i, 1);
    }
  }
  return error;
}

decimal abs_dec(decimal value) {
  if (get_bit(value, 127) != 0) set_bit(&value, 127, 0);
  return value;
}