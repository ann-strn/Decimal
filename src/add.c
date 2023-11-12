#include "decimal.h"

int add(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, sizeof(decimal));
  int overflow = RES_OK;
  int res_sign = 0;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  sign_1 ? set_sign(&value_1, 0) : 0;
  sign_2 ? set_sign(&value_2, 0) : 0;

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);

  if (is_not_equal(value_1, value_2)) normalizator(&value_1, &value_2);

  if (sign_1 && sign_2) {
    overflow = addition(value_1, value_2, result);
    res_sign = sign_1;
    set_sign(result, sign_1);
  } else if (!sign_1 && !sign_2) {
    overflow = addition(value_1, value_2, result);
    res_sign = 0;
  } else if (!sign_1 && sign_2) {
    sub(value_1, value_2, result);
    if (comparison_mantissa(value_1, value_2) == LESS) res_sign = 1;
  } else if (sign_1 && !sign_2) {
    sub(value_1, value_2, result);
    if (comparison_mantissa(value_1, value_2) == MORE) res_sign = 1;
  }

  if (overflow && res_sign) overflow = RES_MIN_OVERFLOW;
  if (overflow == RES_OK) {
    int max_scale = scale_1 > scale_2 ? scale_1 : scale_2;
    set_scale(result, max_scale);
    set_sign(result, res_sign);
  } else {
    memset(result, 0, sizeof(decimal));
  }

  return overflow;
}
