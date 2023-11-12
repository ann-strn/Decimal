#include "decimal.h"

unsigned int define_mask(int pos) { return 1u << (pos % 32); }

int get_bit(decimal value, int bit) {
  unsigned int mask = define_mask(bit);
  return (value.bits[bit / 32] & mask) != 0;
}

void set_bit(decimal *value, int bit, int chislo) {
  if (chislo == 1) {
    value->bits[bit / 32] |= (define_mask(bit));
  } else if (chislo == 0) {
    value->bits[bit / 32] &= ~(define_mask(bit));
  }
}

int get_scale(decimal value) { return (value.bits[3] & SCALE) >> 16; }

void set_scale(decimal *value, int stepen) {
  delete_scale(value);
  value->bits[3] = get_bit(*value, 127) << 31 | stepen << 16;
}

void delete_scale(decimal *dec) {
  int sign = get_sign(*dec);
  dec->bits[3] = 0;
  set_sign(dec, sign);
}

int get_sign(decimal dec) { return !!(dec.bits[3] & MINUS); }

void set_sign(decimal *value, int n) { set_bit(value, 127, n); }

int position_of_first_bit(decimal *value) {
  int position = -1;
  int i = 0;
  while (i < 96 && position == -1) {
    if (get_bit(*value, 95 - i) == 1) {
      position = (95 - i);
    }
    i++;
  }
  return position;
}

void declare_to_null(decimal *value) {
  for (int i = 0; i < 128; ++i) {
    set_bit(value, i, 0);
  }
}
