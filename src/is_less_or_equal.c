#include "decimal.h"

int is_less_or_equal(decimal value1, decimal value2) {
  return is_less(value1, value2) || is_equal(value1, value2);
}
