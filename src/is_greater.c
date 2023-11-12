#include "decimal.h"

int is_greater(decimal value1, decimal value2) {
  decimal a = value1;
  decimal b = value2;
  a = check_minus_null(a);
  b = check_minus_null(b);
  int res = 0, znak_a = get_bit(a, 127), znak_b = get_bit(b, 127);
  normalizator(&a, &b);
  int comparison = comparison_mantissa(a, b);
  if (znak_a == 0 && znak_b == 1)
    res = 1;
  else if (znak_a == znak_b) {
    if (comparison == LESS && znak_a && znak_b)
      res = 1;
    else if (comparison == MORE && !znak_a && !znak_b)
      res = 1;
  }
  return res;
}
