#include "decimal.h"

int is_equal(decimal value1, decimal value2) {
  decimal a = value1;
  decimal b = value2;
  int res = 0, znak_a = get_bit(a, 127), znak_b = get_bit(b, 127);
  decimal null = {{0, 0, 0, 0}};
  normalizator(&a, &b);
  int comparison = comparison_mantissa(a, b);
  int comparwnull = comparison_mantissa(a, null);
  if (comparison == EQUAL && comparwnull == EQUAL) {
    res = 1;
  } else if (znak_a == znak_b) {
    if (comparison == EQUAL) {
      res = 1;
    }
  }
  return res;
}
