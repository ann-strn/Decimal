#include "decimal.h"

int from_int_to_decimal(int src, decimal *dst) {
  int result = 1;
  if (dst) {
    declare_to_null(dst);
    if (src != 0) {
      if (src < 0) {
        set_sign(dst, 1);
        dst->bits[0] = -1 * src;
      } else {
        dst->bits[0] = src;
      }
    }
    result = 0;
  }
  return result;
}
