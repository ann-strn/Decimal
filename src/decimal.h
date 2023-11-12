#ifndef DECIMAL_H_
#define DECIMAL_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -1 * MAX_DECIMAL
#define MAX_SCALE 28
#define MAX_FLOAT 1.0E-28
#define INF 1.0 / 0.0
#define NAN 0.0 / 0.0
#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000  // 00000000 11111111 00000000 00000000

enum { low, mid, high, scale };

typedef struct {
  unsigned int bits[4];
} decimal;

enum result_func { RES_OK, RES_OVERFLOW, RES_MIN_OVERFLOW };
enum comparison { EQUAL, MORE, LESS };
enum round { NO_ROUND, ROUND, ROUND_B, ROUND_MOD };

/*
 ARITHMETIC FUNCTIONS
 0 - OK
 1 - the number is too large or equal to infinity
 2 - the number is too small or equal to negative infinity
 3 - division by 0;
*/

int add(decimal value_1, decimal value_2, decimal *result);
int sub(decimal value_1, decimal value_2, decimal *result);
int mul(decimal value_1, decimal value_2, decimal *result);
int div(decimal value_1, decimal value_2, decimal *result);

/*
COMPARISON FUNCTIONS
 0 - FALSE
 1 - TRUE
*/

int is_less(decimal, decimal);              // <
int is_less_or_equal(decimal, decimal);     // <=
int is_greater(decimal, decimal);           // >
int is_greater_or_equal(decimal, decimal);  // >=
int is_equal(decimal, decimal);             // ==
int is_not_equal(decimal, decimal);         // !=

/*
CONVERTATION FUNCTIONS
 0 - OK
 1 - ERROR
*/

int from_int_to_decimal(int src, decimal *dst);
int from_float_to_decimal(float src, decimal *dst);
int from_decimal_to_int(decimal src, int *dst);
int from_decimal_to_float(decimal src, float *dst);

/*
OTHER DECIMAL FUNCTIONS
 0 - OK
 1 - ERROR
*/

int floor(decimal value, decimal *result);
int round(decimal value, decimal *result);
int truncate(decimal value, decimal *result);
int negate(decimal value, decimal *result);
void fill_decimals_with_zeros(decimal *val);

/* UTILTY FUNCTIONS */
unsigned int define_mask(int pos);
int get_bit(decimal dec, int pos);
void set_bit(decimal *dec, int pos, int bit);
void clearBit(decimal *dec, int pos);
int get_scale(decimal dec);
void setScale(decimal *dec);
int equal(decimal num1, decimal num2);
int is_zero(decimal number);
void decimal_copy(decimal original, decimal *res);
void declare_to_null(decimal *value);
int position_of_first_bit(decimal *value);
decimal abs_dec(decimal value);

/* SCALE */
int get_scale(decimal dec);
void delete_scale(decimal *dec);
void set_scale(decimal *dec, int pow);

/* SIGN */
int get_sign(decimal dec);
void set_sign(decimal *dec, int sign);

/* SHIFTS */
void right_shift(decimal *value, int shift);
int left_shift(decimal *value, int shift);

/* HELPER ARITHMETIC_FUNC */
void normalizator(decimal *value1, decimal *value2);
int addition(decimal value1, decimal value2, decimal *res);
int multiplication(decimal value1, decimal value2, decimal *res);
void substraction(decimal value1, decimal value2, decimal *res);
int division(decimal value1, decimal value2, decimal *res,
             decimal *mod, int round);
int mult_by_10(decimal ten, decimal *ten_res);
void div_by_ten(decimal *value);
int comparison_mantissa(decimal value1, decimal value2);
int count_of_shift(decimal value1, decimal value2, decimal *res);
decimal round_div_mantissa(decimal a, decimal b, decimal *res,
                               int round);
decimal check_minus_null(decimal value);

/* HELPER COMPARISON FUNCTIONS */
int is_zero(decimal number);
int comparison_value_bits(decimal num1, decimal num2);
#endif