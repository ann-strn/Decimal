#include "decimal.h"

int from_decimal_to_int(decimal src, int *dst) {
  if (dst == NULL) {
    return 1;
  }

  int err = 1;
  truncate(src, &src);
  int numSign = get_sign(src);

  if (src.bits[1] || src.bits[2] || src.bits[3] ||
      (numSign && src.bits[0] > 2147483648U) ||
      (!numSign && src.bits[0] > 2147483647)) {
    err = 1;
  }

  *dst = src.bits[0];
  if (numSign) *dst *= -1;

  return err;
}