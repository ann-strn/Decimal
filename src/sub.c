#include "decimal.h"

int sub(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, sizeof(decimal));
  int overflow = RES_OK;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  set_sign(&value_2, 0);
  set_sign(&value_1, 0);

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);

  if (sign_1 != sign_2) {
    overflow = add(value_1, value_2, result);
    set_sign(result, sign_1);

  } else {
    if (scale_1 != scale_2) normalizator(&value_1, &value_2);

    if (is_greater_or_equal(value_1, value_2)) {
      substraction(value_1, value_2, result);
      set_sign(result, sign_1);
      set_scale(result, get_scale(value_1));

    } else {
      substraction(value_2, value_1, result);
      set_sign(result, sign_2 ? 0 : 1);
      set_scale(result, get_scale(value_2));
    }
  }
  if (overflow) overflow = RES_MIN_OVERFLOW;
  return overflow;
}
