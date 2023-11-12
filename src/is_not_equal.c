#include "decimal.h"

int is_not_equal(decimal value1, decimal value2) {
  int res = 1;
  if (is_equal(value1, value2)) {
    res = 0;
  }
  return res;
}
