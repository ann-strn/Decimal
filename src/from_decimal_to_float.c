#include "decimal.h"

int from_decimal_to_float(decimal src, float *dst) {
  int result = 0;

  if (!dst) {
    result = 1;
  } else {
    int scale = get_scale(src);
    long double tmp = 0;

    for (int i = 0; i < 96; i++) tmp += pow(2, i) * get_bit(src, i);

    while (scale--) tmp /= 10.0;

    if (get_sign(src)) tmp *= -1.0;

    *dst = tmp;
  }
  return result;
}
