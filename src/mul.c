#include "decimal.h"

int mul(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, sizeof(decimal));
  int overflow = RES_OK;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int res_sign = sign_1 && sign_2 ? 1 : 0;
  res_sign = !res_sign ? sign_1 || sign_2 : 0;
  set_sign(&value_2, 0);
  set_sign(&value_1, 0);

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);

  if (is_not_equal(value_1, value_2)) normalizator(&value_1, &value_2);

  overflow = multiplication(value_1, value_2, result);
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
