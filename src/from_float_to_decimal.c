#include "decimal.h"

int from_float_to_decimal(float src, decimal *dst) {
  int result = 0;
  if (isnan(src) || isinf(src) || fabsf(src) > MAX_DECIMAL) result = 1;

  if (dst && !result) {
    declare_to_null(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = fabsf(src);
      // src = -(src);
    }

    int new = (int)src;
    int exp = 0;
    // цикл проверяет остался ли остаток разницы между src new, если нет то
    // десяток прибавляется
    while (src - ((float)new / (int)(pow(10, exp))) != 0) {
      // находим нужную степень
      exp++;
      // здесь будет всегда целочисленное значение, т.е. 123, а не 12,3
      new = src *(int)(pow(10, exp));
    }
    from_int_to_decimal(new, dst);

    if (sign) negate(*dst, dst);

    set_scale(dst, exp);
  } else {
    result = 1;
  }
  return result;
}