#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"
#define VERY_LITTLE_DIGIT 1e-10L

typedef struct parametrs {
  int minus;          // '-'
  int plus;           // '+'
  int space;          // ' '
  int hash;           //'#'
  int zero;           //'0'
  int width;          // ширина
  char length;        // длина
  int accuracy;       // точность
  int number_system;  // система исчисления
  int upper;          // верхний регистр
  int spec_e;
  int spec_g;
  int special_case;
} parametrs;

int s21_sprintf(char* str, const char* format, ...);
const char* search_parametrs(parametrs* param, va_list* args,
                             const char* format);
const char* get_flags(parametrs* param, const char* format);
const char* get_width_or_accuracy(va_list* args, int* width_or_accuracy,
                                  const char* format);
const char* get_length(parametrs* param, const char* format);
void default_parameters(char format, parametrs* param);
char* cpecifiers_actions(char* str, const char* format, parametrs* param,
                         va_list* args);
char* spec_s(char* str, parametrs param, va_list* args);
char* buff_to_str(char* str, const char* buffer, int buffer_size);
int buff_size_unsigned(parametrs param, unsigned long long int number_from_arg,
                       int* digits);
char num_to_char(int number, int upper);
char* print_unsigned(char* str, parametrs param,
                     unsigned long long int number_from_arg);
char* spec_p(char* str, parametrs param, va_list* args);
char* spec_ouxX(char* str, parametrs param, va_list* args);
char* spec_c(char* str, parametrs param, va_list* args);
char* ftoa(char* str, parametrs params, va_list* args);
char* add_specs_to_string(char* str, parametrs param, int negative,
                          const char* buffer);
int buff_size_signed(parametrs param, long int number_from_arg, int* digits);
char* spec_d(char* str, parametrs param, va_list* args);
char* print_prefix(char* str, parametrs param, int is_negative);
void infinite_to_string(char* buffer, int upper, long double number_from_arg);
void float_to_string(char* buffer, parametrs param, long double int_part,
                     long double frac_part, int bsize, int exp);
int buff_size_double(parametrs param, long double int_part_double);
int normalize(long double* number_from_arg);
void decision_for_G_point(long double* number_from_arg, parametrs* param,
                          int* exp);
void trim_extra_zero(long double* frac_part, parametrs* param);
#endif
