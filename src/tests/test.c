#include <check.h>
#include <stdlib.h>

#include "../decimal.h"

enum arithmetic_error_code {
  arth_ok,
  arth_large_number,  // 1
  arth_small_number,  // 2
  arth_div_zero       // 3
};

/*
0 - OK
1 - the number is too large or equal to infinity
2 - the number is too small or equal to negative infinity
3 - division by 0;
*/

// SUBSTRACTION

START_TEST(sub_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 155;
  value_2.bits[0] = 55;
  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 100;
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  memset(&result, 0, sizeof(decimal));
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  sub(value_1, value_2, &result);
  int sign = get_sign(result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(decimal));
  set_scale(&value_2, 2);
  test.bits[0] = 4850;
  sub(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 2);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(sub_normal2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};

  value_1.bits[0] = 155;
  value_2.bits[0] = 55;
  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 100;
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  memset(&result, 0, sizeof(decimal));
  value_1.bits[0] = (unsigned int)50;
  value_2.bits[0] = (unsigned int)150;
  sub(value_1, value_2, &result);
  int sign = get_sign(result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(sign, 1);

  memset(&value_1, 0, sizeof(decimal));
  memset(&value_2, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  value_1.bits[0] = (unsigned int)50;
  value_2.bits[0] = (unsigned int)15;
  memset(&result, 0, sizeof(decimal));
  set_scale(&value_2, 1);
  sub(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], 485);
  ck_assert_uint_eq(get_scale(result), 1);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(sub_inf) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 55;
  set_sign(&value_1, 1);
  int res = sub(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(sub_inf2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 55;
  set_sign(&value_1, 1);
  int res = sub(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(sub_one_sign) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 200;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(decimal));
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(sub_one_sign2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 200;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(decimal));
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(sub_two_sign) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 100;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(decimal));
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 1);

  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  memset(&result, 0, sizeof(decimal));
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 1);
}
END_TEST

START_TEST(sub_two_sign2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);

  sub(value_1, value_2, &result);
  decimal test = {0};
  test.bits[0] = 100;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);

  memset(&result, 0, sizeof(decimal));
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 1);

  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  memset(&result, 0, sizeof(decimal));
  sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(sum_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(sum_both_neg) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  set_scale(&value_2, 1);
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(sum_error) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, arth_large_number);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(decimal));
  res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(sum_normal2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  int res = add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(sum_both_neg2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  set_scale(&value_2, 1);
  int res = add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(sum_error2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);

  memset(&result, 0, sizeof(decimal));
  res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(part1_add_one_greater) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  decimal test = {{20}};
  set_sign(&value_2, 1);
  add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_add_one_greater2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  decimal test = {{20}};
  set_sign(&value_1, 1);
  add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part1_add_one_sign) {
  decimal value_1 = {{150}};
  decimal value_2 = {{50}};
  decimal result = {0};
  decimal test = {{100}};
  set_sign(&value_1, 1);
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(decimal));
  int res = add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(one_sign) {
  decimal value_1 = {{150}};
  decimal value_2 = {{50}};
  decimal result = {0};
  decimal test = {{100}};
  set_sign(&value_1, 1);
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(decimal));
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

// DIVISION

START_TEST(div_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(div_both_neg) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  set_scale(&value_2, 1);
  div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(div_error) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = div(value_1, value_2, &result);
  ck_assert_int_eq(res, arth_large_number);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(decimal));
  res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(div_normal2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  int res = div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(div_both_neg2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  set_scale(&value_2, 1);
  int res = div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(div_error2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);

  memset(&result, 0, sizeof(decimal));
  res = add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(part1_div_one_greater) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  decimal test = {{20}};
  set_sign(&value_2, 1);
  div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_div_one_greater2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  decimal test = {{20}};
  set_sign(&value_1, 1);
  div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part1_div_one_sign) {
  decimal value_1 = {{150}};
  decimal value_2 = {{50}};
  decimal result = {0};
  decimal test = {{100}};
  set_sign(&value_1, 1);
  div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(decimal));
  int res = add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(div_sign) {
  decimal value_1 = {{150}};
  decimal value_2 = {{50}};
  decimal result = {0};
  decimal test = {{100}};
  set_sign(&value_1, 1);
  div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(decimal));
  add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

// MULTIPLY

START_TEST(mul_value_1_is_one) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(decimal));
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(mul_value_2_is_one) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(mul_value_1_is_zero) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(mul_value_2_is_zero) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(mul_max) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  set_scale(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  memset(&test, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_big_power) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 255;
  test.bits[0] = 4294967041;
  test.bits[1] = 254;
  set_scale(&value_2, 10);
  int res = mul(value_1, value_2, &result);
  memset(&test, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_big_negative_over) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  set_scale(&value_2, 1);
  set_sign(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, arth_small_number);
}
END_TEST

START_TEST(mul_big_over) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  set_scale(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, arth_large_number);
}
END_TEST

START_TEST(mul_norm) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  set_scale(&value_2, 4);
  int res = mul(value_1, value_2, &result);
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_value_1_is_minus) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  set_sign(&value_1, 1);
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(mul_value_2_is_minus) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 15;
  set_sign(&value_2, 1);
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(mul_value_1_is_zero_minus) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  set_sign(&value_1, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(mul_value_2_is_zero_minus) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 7;
  set_sign(&value_2, 1);
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(mul_value_1_2_is_minus) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(mul_max_1) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  set_sign(&value_1, 1);
  value_2.bits[0] = 5;
  set_sign(&value_2, 1);
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  set_scale(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  memset(&test, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_max_2) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  value_1.bits[0] = 4294967295;
  set_sign(&value_1, 1);
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  set_scale(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  memset(&test, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_max_3) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  decimal test = {0};
  set_sign(&value_1, 1);
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  set_scale(&value_2, 1);
  int res = mul(value_1, value_2, &result);
  memset(&test, 0, sizeof(decimal));
  memset(&result, 0, sizeof(decimal));
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_scale(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

// COMPARISON

START_TEST(is_less_null) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(is_less(value_1, value_2), 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_less(value_1, value_2), 1);
    ck_assert_int_eq(is_less(value_2, value_1), 0);
  }
}
END_TEST

START_TEST(is_less_negative) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  ck_assert_int_eq(is_less(value_1, value_2), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_pow) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  set_scale(&value_1, 8);
  set_scale(&value_2, 8);
  ck_assert_int_eq(is_less(value_1, value_2), 0);
  set_scale(&value_2, 0);
  ck_assert_int_eq(is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_less_or_equal(value_1, value_2), 1);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_less_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(is_less_or_equal_with_sign) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_less_or_equal(value_1, value_2), 0);
  set_sign(&value_1, 1);
  ck_assert_int_eq(is_less_or_equal(value_1, value_2), 1);
  set_sign(&value_1, 0);
  ck_assert_int_eq(is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(is_greater_null) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(is_greater(value_1, value_2), 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(is_greater_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_greater(value_1, value_2), 0);
    ck_assert_int_eq(is_greater(value_2, value_1), 1);
  }
}
END_TEST

START_TEST(is_greater_negative) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  ck_assert_int_eq(is_greater(value_1, value_2), 0);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_greater_two_negative) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(is_greater_or_equal_normal) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_greater_or_equal(value_1, value_2), 0);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(is_greater_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(is_greater_or_equal_with_sign) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2, 1);
  ck_assert_int_eq(is_greater_or_equal(value_1, value_2), 1);
  set_sign(&value_1, 1);
  ck_assert_int_eq(is_greater_or_equal(value_1, value_2), 1);
  set_sign(&value_2, 0);
  ck_assert_int_eq(is_greater_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(one_greater) {
  decimal value_1 = {0};
  decimal value_2 = {0};
  decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  decimal test = {{20}};
  set_sign(&value_2, 1);
  add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(isEqual_1) {
  decimal a = {{48, 0}}, b = {{48, 0}};
  ck_assert_uint_eq(is_equal(a, b), 1);
}
END_TEST

START_TEST(isEqual_2) {
  decimal a = {{1, 1, 0, 0}}, b = {{1, 1, 1, 0}};
  ck_assert_uint_eq(is_equal(a, b), 0);
}
END_TEST

START_TEST(not_equal_null) {
  decimal value = {0};
  decimal test = {0};
  int res = is_not_equal(value, test);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(not_equal_normal) {
  decimal value = {{5}};
  decimal test = {{6}};
  int res = is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(not_equal_negative) {
  decimal value = {{5}};
  decimal test = {{5}};
  set_sign(&value, 1);
  int res = is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(int_and_decimal_max) {
  decimal value_1 = {0};
  value_1.bits[0] = 4294967295;
  int a = 0;
  int res = from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(int_and_decimal_big_pow) {
  decimal value_1 = {0};
  int result = 184467440;
  value_1.bits[0] = 344;
  value_1.bits[1] = 4294967295;
  int a = 0;
  set_scale(&value_1, 11);
  from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(int_and_decimal_int_overflow) {
  decimal value_1 = {0};
  value_1.bits[0] = 2147483650U;
  set_sign(&value_1, 1);
  int a = 0;
  ck_assert_int_eq(from_decimal_to_int(value_1, &a), 1);
}
END_TEST

START_TEST(int_and_decimal_error) {
  decimal value_1 = {0};
  value_1.bits[0] = 2147483648;
  int a = 0;
  set_sign(&value_1, 1);
  int res = from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(res, 1);
  decimal value_2 = {0};
  int *b = NULL;
  res = from_decimal_to_int(value_2, b);
  ck_assert_int_eq(res, 1);
  decimal *dst = NULL;
  int c = 0;
  res = from_int_to_decimal(c, dst);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(int_and_decimal_sign) {
  decimal value_1 = {0};
  int a = -5;
  decimal test = {{5}};
  from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 1);
}
END_TEST

START_TEST(int_and_decimal_whith_pow) {
  decimal value_1 = {0};
  int a = 0;
  value_1.bits[0] = 5;
  set_scale(&value_1, 20);
  from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(int_and_decimal_nul) {
  decimal value_1 = {0};
  decimal test = {0};
  int a = 0;
  from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 0);
  a = 123456;
  test.bits[0] = 123456;
  from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  set_sign(&value_1, 1);
  int b = 0;
  from_decimal_to_int(value_1, &b);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 1);
}
END_TEST

// ROUND

START_TEST(part1_round_zero) {
  decimal value_1 = {0};
  decimal result = {0};
  decimal test = {0};
  set_scale(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part2_round_one) {
  decimal value_1 = {{1, 0, 0, 0}};
  decimal result = {0};
  decimal test = {{1, 0, 0, 0}};
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part3_round_num) {
  decimal value_1 = {{422142, 0, 0, 0}};
  decimal result = {0};
  decimal test = {{422142, 0, 0, 0}};
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part4_round_pow1) {
  decimal value_1 = {{4221425, 0, 0, 0}};
  decimal result = {0};
  decimal test = {{422143, 0, 0, 0}};
  set_scale(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part5_round_pow2) {
  decimal value_1 = {{4221424, 0, 0, 0}};
  decimal result = {0};
  decimal test = {{422142, 0, 0, 0}};
  set_scale(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part6_round_pow3) {
  decimal value_1 = {{4221426, 0, 0, 0}};
  decimal result = {0};
  decimal test = {{422143, 0, 0, 0}};
  set_scale(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part7_round_pow4) {
  decimal value_1 = {{422142, 422142, 0, 0}};
  decimal result = {0};
  decimal test = {{609885778, 422, 0, 0}};
  set_scale(&value_1, 3);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(part8_round_pow5) {
  decimal value_1 = {{420521, 422142, 0, 0}};
  decimal result = {0};
  decimal test = {{609885777, 422, 0, 0}};
  set_scale(&value_1, 3);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);

  set_sign(&value_1, 1);
  round(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_positive_integer) {
  decimal result = {0};
  decimal value = {0};
  value.bits[0] = 7;
  decimal test = {{7}};
  int result = floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(result, arth_ok);
}
END_TEST

START_TEST(floor_null) {
  decimal *result = NULL;
  decimal value = {0};
  int result = floor(value, result);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(floor_negative_integer) {
  decimal result = {0};
  decimal value = {0};
  value.bits[0] = 12;
  decimal test = {{12}};
  set_sign(&value, 1);
  int result = floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(result, arth_ok);
}
END_TEST

START_TEST(floor_positive_non_integer) {
  decimal result = {0};
  decimal value = {0};
  value.bits[0] = 2463;
  decimal test = {{2}};
  set_scale(&value, 3);
  int result = floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(result, arth_ok);
}
END_TEST

START_TEST(floor_negative_non_integer) {
  decimal result = {0};
  decimal value = {0};
  value.bits[0] = 2463;
  decimal test = {{3}};
  set_sign(&value, 1);
  set_scale(&value, 3);
  int result = floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(result, arth_ok);
}
END_TEST

START_TEST(floor_zero) {
  decimal result = {0};
  decimal value = {0};
  decimal test = {0};
  int result = floor(value, &result);
  ck_assert_int_eq(result, arth_ok);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(truncate_normal) {
  decimal value_1 = {0};
  decimal result = {0};
  decimal test = {{150}};
  value_1.bits[0] = 150;
  truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(truncate_null) {
  decimal value_1 = {0};
  decimal result = {0};
  decimal test = {{0}};
  truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(truncate_negative) {
  decimal value_1 = {{150}};
  decimal result = {0};
  decimal test = {{150}};
  set_sign(&value_1, 1);
  truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(truncate_pow) {
  decimal value_1 = {{154345}};
  decimal result = {0};
  decimal test = {{154}};
  set_sign(&value_1, 1);
  set_scale(&value_1, 3);
  truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(negate_normal) {
  decimal value_1 = {{154345}};
  decimal result = {0};
  decimal test = {{154345}};
  set_sign(&value_1, 1);
  negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(negate_null) {
  decimal value_1 = {{0}};
  decimal result = {0};
  decimal test = {0};
  negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(negate_negative) {
  decimal value_1 = {{123455}};
  decimal result = {0};
  decimal test = {{123455}};
  set_sign(&value_1, 1);
  negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(negate_pow) {
  decimal value_1 = {{123455}};
  decimal result = {0};
  decimal test = {{123455}};
  set_sign(&value_1, 1);
  set_scale(&value_1, 3);
  negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 3);
}
END_TEST

START_TEST(decimal_float_normal) {
  decimal value = {{8}};
  float a = 0;
  float b = 8.0;
  from_decimal_to_float(value, &a);
  ck_assert_int_eq(get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(decimal_float_null) {
  decimal value = {0};
  float a = 0.0;
  float b = 0.0;
  from_decimal_to_float(value, &a);
  ck_assert_int_eq(get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(decimal_float_power) {
  decimal value = {{8}};
  float a = 0.0;
  float b = -0.8;
  set_scale(&value, 1);
  set_sign(&value, 1);
  from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(decimal_float_big_power) {
  decimal value = {{8}};
  float a = 0.0;
  float b = -0.0000000000000000000000000008;
  set_scale(&value, 28);
  set_sign(&value, 1);
  from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(decimal_float_power_max_value) {
  decimal value = {0};
  value.bits[0] = 147484107;
  float a = 0.0;
  float b = -1.47484107;
  set_scale(&value, 8);
  set_sign(&value, 1);
  from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(decimal_float_power_max_dec) {
  decimal value = {0};
  value.bits[0] = 214748;
  float a = 0.0;
  float b = -0.00000214748;
  set_scale(&value, 11);
  set_sign(&value, 1);
  from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(decimal_float_error) {
  decimal value = {0};
  float *a = NULL;
  int res = from_decimal_to_float(value, a);
  ck_assert_uint_eq(res, 1);
}
END_TEST

// FLOAT

START_TEST(float_dec_normal) {
  decimal value_2 = {0};
  decimal test = {0};
  float a = 0.8;
  set_scale(&test, 1);
  int res = from_float_to_decimal(a, &value_2);
  ck_assert_uint_eq(res, 0);
  ck_assert_uint_eq(get_scale(value_2), get_scale(test));
}
END_TEST

START_TEST(float_dec_negative) {
  decimal value_2 = {0};
  decimal test = {0};
  float a = -12.8;
  set_scale(&test, 1);
  int res = from_float_to_decimal(a, &value_2);
  ck_assert_uint_eq(res, 0);
  ck_assert_uint_eq(get_scale(value_2), get_scale(test));
}
END_TEST

START_TEST(float_dec_error) {
  decimal *value_2 = NULL;
  float a = -12.8;
  int res = from_float_to_decimal(a, value_2);
  ck_assert_uint_eq(res, 1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sub_normal);
  tcase_add_test(tc1_1, sub_inf);
  tcase_add_test(tc1_1, sub_one_sign);
  tcase_add_test(tc1_1, sub_two_sign);
  tcase_add_test(tc1_1, sub_normal);
  tcase_add_test(tc1_1, sub_normal2);
  tcase_add_test(tc1_1, sub_inf2);
  tcase_add_test(tc1_1, sub_one_sign2);
  tcase_add_test(tc1_1, sub_two_sign2);
  tcase_add_test(tc1_1, sub_normal);
  tcase_add_test(tc1_1, sub_inf);
  tcase_add_test(tc1_1, sub_one_sign);
  tcase_add_test(tc1_1, sub_two_sign);

  tcase_add_test(tc1_1, sum_normal);
  tcase_add_test(tc1_1, sum_both_neg);
  tcase_add_test(tc1_1, sum_error);
  tcase_add_test(tc1_1, sum_normal2);
  tcase_add_test(tc1_1, sum_both_neg2);
  tcase_add_test(tc1_1, sum_error2);
  tcase_add_test(tc1_1, part1_add_one_sign);
  tcase_add_test(tc1_1, part1_add_one_greater);
  tcase_add_test(tc1_1, part1_add_one_greater2);
  tcase_add_test(tc1_1, one_sign);

  tcase_add_test(tc1_1, div_normal);
  tcase_add_test(tc1_1, div_both_neg);
  tcase_add_test(tc1_1, div_error);
  tcase_add_test(tc1_1, div_normal2);
  tcase_add_test(tc1_1, div_both_neg2);
  tcase_add_test(tc1_1, div_error2);
  tcase_add_test(tc1_1, part1_div_one_sign);
  tcase_add_test(tc1_1, part1_div_one_greater);
  tcase_add_test(tc1_1, part1_div_one_greater2);
  tcase_add_test(tc1_1, div_sign);

  tcase_add_test(tc1_1, mul_value_1_is_one);
  tcase_add_test(tc1_1, mul_value_2_is_one);
  tcase_add_test(tc1_1, mul_value_1_is_zero);
  tcase_add_test(tc1_1, mul_value_2_is_zero);
  tcase_add_test(tc1_1, mul_big_negative_over);
  tcase_add_test(tc1_1, mul_big_over);
  tcase_add_test(tc1_1, mul_value_1_is_minus);
  tcase_add_test(tc1_1, mul_value_2_is_minus);
  tcase_add_test(tc1_1, mul_value_1_is_zero_minus);
  tcase_add_test(tc1_1, mul_value_2_is_zero_minus);
  tcase_add_test(tc1_1, mul_value_1_2_is_minus);
  tcase_add_test(tc1_1, mul_max);
  tcase_add_test(tc1_1, mul_big_power);
  tcase_add_test(tc1_1, mul_norm);
  tcase_add_test(tc1_1, mul_max_1);
  tcase_add_test(tc1_1, mul_max_2);
  tcase_add_test(tc1_1, mul_max_3);

  tcase_add_test(tc1_1, is_less_null);
  tcase_add_test(tc1_1, is_less_normal);
  tcase_add_test(tc1_1, is_less_negative);
  tcase_add_test(tc1_1, is_less_pow);

  tcase_add_test(tc1_1, is_less_or_equal_normal);
  tcase_add_test(tc1_1, is_less_or_equal_with_sign);

  tcase_add_test(tc1_1, is_greater_null);
  tcase_add_test(tc1_1, is_greater_normal);
  tcase_add_test(tc1_1, is_greater_negative);
  tcase_add_test(tc1_1, is_greater_two_negative);
  tcase_add_test(tc1_1, is_greater_or_equal_normal);
  tcase_add_test(tc1_1, is_greater_or_equal_with_sign);
  tcase_add_test(tc1_1, one_greater);

  tcase_add_test(tc1_1, isEqual_1);
  tcase_add_test(tc1_1, isEqual_2);
  tcase_add_test(tc1_1, not_equal_null);
  tcase_add_test(tc1_1, not_equal_normal);
  tcase_add_test(tc1_1, not_equal_negative);

  tcase_add_test(tc1_1, int_and_decimal_max);
  tcase_add_test(tc1_1, int_and_decimal_big_pow);
  tcase_add_test(tc1_1, int_and_decimal_int_overflow);
  tcase_add_test(tc1_1, int_and_decimal_error);
  tcase_add_test(tc1_1, int_and_decimal_sign);
  tcase_add_test(tc1_1, int_and_decimal_whith_pow);
  tcase_add_test(tc1_1, int_and_decimal_nul);

  tcase_add_test(tc1_1, float_dec_normal);
  tcase_add_test(tc1_1, float_dec_negative);
  tcase_add_test(tc1_1, float_dec_error);

  tcase_add_test(tc1_1, decimal_float_normal);
  tcase_add_test(tc1_1, decimal_float_null);
  tcase_add_test(tc1_1, decimal_float_power);
  tcase_add_test(tc1_1, decimal_float_big_power);
  tcase_add_test(tc1_1, decimal_float_power_max_value);
  tcase_add_test(tc1_1, decimal_float_power_max_dec);
  tcase_add_test(tc1_1, decimal_float_error);

  tcase_add_test(tc1_1, part1_round_zero);
  tcase_add_test(tc1_1, part2_round_one);
  tcase_add_test(tc1_1, part3_round_num);
  tcase_add_test(tc1_1, part4_round_pow1);
  tcase_add_test(tc1_1, part5_round_pow2);
  tcase_add_test(tc1_1, part6_round_pow3);
  tcase_add_test(tc1_1, part7_round_pow4);
  tcase_add_test(tc1_1, part8_round_pow5);

  tcase_add_test(tc1_1, floor_positive_integer);
  tcase_add_test(tc1_1, floor_null);
  tcase_add_test(tc1_1, floor_negative_integer);
  tcase_add_test(tc1_1, floor_positive_non_integer);
  tcase_add_test(tc1_1, floor_negative_non_integer);
  tcase_add_test(tc1_1, floor_zero);

  tcase_add_test(tc1_1, truncate_normal);
  tcase_add_test(tc1_1, truncate_null);
  tcase_add_test(tc1_1, truncate_negative);
  tcase_add_test(tc1_1, truncate_pow);

  tcase_add_test(tc1_1, negate_normal);
  tcase_add_test(tc1_1, negate_null);
  tcase_add_test(tc1_1, negate_negative);
  tcase_add_test(tc1_1, negate_pow);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}