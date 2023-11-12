#include "decimal.h"

int is_greater_or_equal(decimal value1, decimal value2) {
  return is_greater(value1, value2) || is_equal(value1, value2);
}
