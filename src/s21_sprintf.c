#include "s21_string.h"

int s21_sprintf(char* str, const char* format, ...) {
  int flag = -1;
  const char* str_before_edit = str;
  va_list args;
  va_start(args, format);

  for (; *format; format++) {
    if (*format == '%') {
      parametrs param = {0};
      param.accuracy = -1, param.number_system = 10;
      format++;
      format = search_parametrs(&param, &args, format);
      str = cpecifiers_actions(str, format, &param, &args);
    } else {
      *(str++) = *format;
    }
  }
  va_end(args);

  if (str) {
    *str = '\0';
    flag = str - str_before_edit;
  }
  return flag;
}

const char* search_parametrs(parametrs* param, va_list* args,
                             const char* format) {
  format = get_flags(param, format);
  format = get_width_or_accuracy(args, &(param->width), format);
  if (*format == '.') {
    format = get_width_or_accuracy(args, &(param->accuracy), ++format);
  }
  format = get_length(param, format);

  if (param->width < 0) {
    param->width *= -1;
    param->minus = 1;
  }
  return format;
}

const char* get_flags(parametrs* param, const char* format) {
  while (*format && s21_strchr("-+ #0", *format)) {
    if (*format == '-') param->minus = 1;
    if (*format == '+') param->plus = 1;
    if (*format == ' ') param->space = 1;
    if (*format == '#') param->hash = 1;
    if (*format == '0') param->zero = 1;
    format++;
  }

  if (param->minus && param->zero) param->zero = 0;
  if (param->space && param->plus) param->space = 0;

  return format;
}

const char* get_width_or_accuracy(va_list* args, int* width_or_accuracy,
                                  const char* format) {
  *width_or_accuracy = 0;
  if (*format == '*') {
    *width_or_accuracy = va_arg(*args, int);
    format++;
  } else {
    while (*format && s21_strchr("0123456789", *format)) {
      *width_or_accuracy = *width_or_accuracy * 10 + (*format - '0');
      format++;
    }
  }
  return format;
}

const char* get_length(parametrs* param, const char* format) {
  if (s21_strchr("hlL", *format)) param->length = *format++;
  return format;
}

void default_parameters(char format, parametrs* param) {
  if (param->accuracy < 0) {
    const char specifiers[11] = "duoxXpfeEgG";
    for (int i = 0; i < 11; i++) {
      if (format == specifiers[i]) {
        if (i <= 5)
          param->accuracy = 1;
        else
          param->accuracy = 6;
      }
    }
  }
  if (format == 'o')
    param->number_system = 8;
  else if (format == 'x' || format == 'X' || format == 'p')
    param->number_system = 16;
  if (format == 'X' || format == 'G' || format == 'E') param->upper = 1;
  if (format == 'e' || format == 'E') param->spec_e = 1;
  if (format == 'g' || format == 'G') param->spec_g = 1;
  if (format == 'p') param->hash = 1;
  if (format == 'u') param->special_case = 1;
}

char* cpecifiers_actions(char* str, const char* format, parametrs* param,
                         va_list* args) {
  default_parameters(*format, param);

  if (*format == 's') {
    str = spec_s(str, *param, args);
  } else if (*format == 'u' || *format == 'o' || *format == 'x' ||
             *format == 'X') {
    str = spec_ouxX(str, *param, args);
  } else if (*format == 'p') {
    str = spec_p(str, *param, args);
  } else if (*format == 'c') {
    str = spec_c(str, *param, args);
  } else if (*format == 'f' || *format == 'e' || *format == 'E' ||
             *format == 'g' || *format == 'G') {
    str = ftoa(str, *param, args);
  } else if (*format == 'd') {
    str = spec_d(str, *param, args);
  } else if (*format == 'i') {
    str = spec_d(str, *param, args);
  } else if (*format == '%')
    *str++ = *format;
  return str;
}

char* spec_s(char* str, parametrs param, va_list* args) {
  const char* string_from_arg = va_arg(*args, char*);

  if (!string_from_arg) {
    if (param.accuracy >= (int)s21_strlen("(null)") || param.accuracy < 0)
      string_from_arg = "(null)";
    else
      string_from_arg = "";
  }

  int spaces = param.width;
  int len = (int)s21_strlen(string_from_arg);

  if (len >= param.accuracy && param.accuracy >= 0)
    spaces -= param.accuracy;
  else
    spaces -= len;

  for (int i = 0; i < spaces && !param.minus; i++) *str++ = ' ';
  for (int i = 0;
       (param.accuracy < 0 || i < param.accuracy) && *string_from_arg; i++)
    *str++ = *string_from_arg++;
  for (int i = 0; i < spaces && param.minus; i++) *str++ = ' ';

  return str;
}

char* spec_ouxX(char* str, parametrs param, va_list* args) {
  unsigned long long int number_from_arg = 0;

  if (param.length == 'h')
    number_from_arg = (unsigned short)va_arg(*args, unsigned int);
  else if (param.length == 'l')
    number_from_arg = (unsigned long int)va_arg(*args, unsigned long int);
  else
    number_from_arg = (unsigned int)va_arg(*args, unsigned int);

  str = print_unsigned(str, param, number_from_arg);

  return str;
}

char* spec_p(char* str, parametrs param, va_list* args) {
  void* ptr_from_arg = va_arg(*args, void*);
  unsigned long long int ptr_value = (unsigned long long int)ptr_from_arg;
  if (ptr_value)
    str = print_unsigned(str, param, ptr_value);
  else {
    param.special_case = 1;
    str = add_specs_to_string(str, param, 0, "(nil)");
  }

  return str;
}

char* buff_to_str(char* str, const char* buffer, int buffer_size) {
  for (int i = 0; i < buffer_size; i++) {
    *str++ = *buffer++;
  }
  return str;
}

char* print_unsigned(char* str, parametrs param,
                     unsigned long long int number_from_arg) {
  int digits = 0;
  int bsize = buff_size_unsigned(param, number_from_arg, &digits);
  if (number_from_arg == 0 ||
      (param.accuracy > digits && param.number_system == 8))
    param.special_case = 1;
  char* buffer = (char*)malloc(bsize * sizeof(char));
  if (buffer) {
    int current_len = bsize - 1;
    int current_digit = digits;
    int nulls_fore_accuracy = 0;
    if (param.accuracy > digits) nulls_fore_accuracy = param.accuracy - digits;
    buffer[current_len--] = '\0';

    for (; current_digit > 0; current_digit--) {
      buffer[current_len--] =
          num_to_char(number_from_arg % param.number_system, param.upper);
      number_from_arg /= param.number_system;
    }

    for (int i = 0; param.accuracy > digits && i < nulls_fore_accuracy; i++)
      buffer[current_len--] = '0';

    str = add_specs_to_string(str, param, 0, buffer);

    free(buffer);
  }
  return str;
}

int buff_size_unsigned(parametrs param, unsigned long long int number_from_arg,
                       int* digits) {
  if (number_from_arg == 0) {
    *digits = 1;
  } else {
    while (number_from_arg != 0) {
      number_from_arg /= param.number_system;
      (*digits)++;
    }
  }
  int buff_size = *digits;
  if (param.accuracy > *digits) buff_size = param.accuracy;

  return buff_size + 1;
}

char num_to_char(int number, int upper) {
  char symb = '?';
  if (number == 10) symb = (char)('a' - upper * 32);
  if (number == 11) symb = (char)('b' - upper * 32);
  if (number == 12) symb = (char)('c' - upper * 32);
  if (number == 13) symb = (char)('d' - upper * 32);
  if (number == 14) symb = (char)('e' - upper * 32);
  if (number == 15) symb = (char)('f' - upper * 32);
  if (number >= 0 && number <= 9) symb = (char)(number + 48);
  return symb;
}

char* spec_c(char* str, parametrs param, va_list* args) {
  char symbol_from_arg = (char)va_arg(*args, int);

  for (int i = 0; i < (param.width - 1) && !param.minus; i++) *str++ = ' ';
  *str++ = symbol_from_arg;
  for (int i = 0; i < (param.width - 1) && param.minus; i++) *str++ = ' ';

  return str;
}

char* ftoa(char* str, parametrs param, va_list* args) {
  long double num = 0.0;
  int exp = 0;
  if (param.accuracy > 19) param.accuracy = 19;

  if (param.length == 'L')
    num = va_arg(*args, long double);
  else
    num = va_arg(*args, double);

  int is_negative = signbit(num);
  if (is_negative) num = -num;
  int is_digit = !(num == 1.0L / 0.0L || isnan(num));

  if (param.spec_e && is_digit) exp = normalize(&num);
  if (param.spec_g && is_digit) decision_for_G_point(&num, &param, &exp);

  char* result = S21_NULL;
  if (is_digit) {
    long double int_part = 0.0, frac_part = 0.0;
    frac_part = modfl(num, &int_part);
    long double multiplier = powl(10, param.accuracy);
    frac_part = roundl(frac_part * multiplier);
    if (frac_part / multiplier >= 1.0L) {
      int_part += 1.0L;
    }
    trim_extra_zero(&frac_part, &param);
    int bsize = buff_size_double(param, int_part);
    result = malloc(bsize * sizeof(char));
    if (result) float_to_string(result, param, int_part, frac_part, bsize, exp);
  } else {
    result = malloc(4 * sizeof(char));
    if (result) infinite_to_string(result, param.upper, num);
  }
  if (result) {
    str = add_specs_to_string(str, param, is_negative, result);
    free(result);
  }
  return str;
}

char* print_filler(char* str, parametrs param, int buflen, char char_to_add) {
  int need_spases = param.width - buflen;
  for (int i = 0; i < need_spases && need_spases > 0; i++) *str++ = char_to_add;
  return str;
}

char* add_specs_to_string(char* str, parametrs param, int is_negative,
                          const char* buffer) {
  int len = s21_strlen(buffer);
  int icrement = 0;
  char char_to_add = ' ';
  if (param.zero) char_to_add = '0';
  if (param.number_system == 10 && ((param.plus || param.space) || is_negative))
    icrement++;
  if (param.number_system == 16 && param.hash && !param.special_case)
    icrement = 2;
  if (param.number_system == 8 && param.hash && !param.special_case)
    icrement = 1;
  if (!param.minus) {
    if (param.zero) {
      str = print_prefix(str, param, is_negative);
      str = print_filler(str, param, len + icrement, char_to_add);
    } else {
      str = print_filler(str, param, len + icrement, char_to_add);
      str = print_prefix(str, param, is_negative);
    }
    str = buff_to_str(str, buffer, len);
  } else {
    str = print_prefix(str, param, is_negative);
    str = buff_to_str(str, buffer, len);
    char_to_add = ' ';
    str = print_filler(str, param, len + icrement, char_to_add);
  }
  return str;
}

char* spec_d(char* str, parametrs param, va_list* args) {
  long int number_from_arg = 0;
  if (param.length == 'h')
    number_from_arg = (short)va_arg(*args, int);
  else if (param.length == 'l')
    number_from_arg = va_arg(*args, long int);
  else
    number_from_arg = va_arg(*args, int);
  int is_negative = (number_from_arg < 0);
  int digits = 0;
  int bsize = buff_size_signed(param, number_from_arg, &digits);
  if (is_negative) number_from_arg = labs(number_from_arg);
  char* buffer = (char*)malloc(bsize * sizeof(char));

  if (buffer) {
    int current_len = bsize - 1;
    int current_digit = digits;
    int nulls_fore_accuracy = 0;
    if (param.accuracy > digits) nulls_fore_accuracy = param.accuracy - digits;
    buffer[current_len--] = '\0';

    for (; current_digit > 0; current_digit--) {
      buffer[current_len--] =
          num_to_char(labs(number_from_arg % param.number_system), param.upper);
      number_from_arg /= param.number_system;
    }

    for (int i = 0; param.accuracy > digits && i < nulls_fore_accuracy; i++)
      buffer[current_len--] = '0';

    str = add_specs_to_string(str, param, is_negative, buffer);

    free(buffer);
  }

  return str;
}

int buff_size_signed(parametrs param, long int number_from_arg, int* digits) {
  if (number_from_arg == 0 && param.accuracy != 0) {
    *digits = 1;
  } else {
    while (number_from_arg != 0) {
      number_from_arg /= param.number_system;
      (*digits)++;
    }
  }
  int buff_size = *digits;
  if (param.accuracy > *digits) buff_size = param.accuracy;

  return buff_size + 1;
}

char* print_prefix(char* str, parametrs param, int is_negative) {
  if (param.number_system == 10 && !param.special_case) {
    if (param.plus && !is_negative)
      *str++ = '+';
    else if (param.space && !is_negative)
      *str++ = ' ';
    else if (is_negative)
      *str++ = '-';
  }
  if (!param.special_case) {
    if (param.number_system != 10 && param.hash) *str++ = '0';
    if (param.number_system == 16 && param.hash)
      *str++ = param.upper ? 'X' : 'x';
  }
  return str;
}

int buff_size_double(parametrs param, long double int_part_double) {
  int int_digits = 0;
  while (int_part_double >= 1.0L - VERY_LITTLE_DIGIT) {
    int_part_double /= 10.0L;
    int_digits++;
  }

  int buff_size = (int_digits ? int_digits : 1) +
                  (param.accuracy > 0 || param.hash) + param.accuracy;
  if (param.spec_e) buff_size += 4;

  return buff_size + 1;
}

void float_to_string(char* buffer, parametrs param, long double int_part,
                     long double frac_part, int bsize, int exp) {
  int current_len = bsize - 1;

  buffer[current_len--] = '\0';

  if (param.spec_e) {
    buffer[current_len--] = (char)(abs(exp) % 10 + 48);
    buffer[current_len--] = (char)(abs(exp) / 10 + 48);
    buffer[current_len--] = (char)('-' * (exp < 0) + '+' * (exp >= 0));
    buffer[current_len--] = (char)('e' - param.upper * 32);
  }

  for (int i = 0; i < param.accuracy; i++, frac_part /= 10.0L)
    buffer[current_len--] =
        num_to_char((int)(frac_part - floorl(frac_part / 10.0L) * 10), 0);
  if (param.accuracy || param.hash) buffer[current_len--] = '.';

  for (; int_part >= 10; int_part /= 10.0L)
    buffer[current_len--] =
        num_to_char((int)(int_part - floorl(int_part / 10.0L) * 10), 0);
  buffer[current_len] = num_to_char((int)int_part, 0);
}

void infinite_to_string(char* buffer, int upper, long double number_from_arg) {
  if (isnan(number_from_arg)) {
    s21_strcpy(buffer, upper ? "NAN" : "nan");
  } else {
    s21_strcpy(buffer, upper ? "INF" : "inf");
  }
}

int normalize(long double* number_from_arg) {
  int exp = 0;

  if (*number_from_arg != 0) exp = (int)floorl(log10l(*number_from_arg));

  *number_from_arg = *number_from_arg / powl(10.0L, exp);

  return exp;
}

void decision_for_G_point(long double* number_from_arg, parametrs* param,
                          int* exp) {
  long double temp_number = *number_from_arg;
  int temp_exp = normalize(&temp_number);
  if (!param->accuracy) param->accuracy = 1;
  if (temp_exp < -4 || temp_exp >= param->accuracy) {
    param->spec_e = 1;
    *exp = temp_exp;
    *number_from_arg = temp_number;
    param->accuracy -= 1;
  } else
    param->accuracy = param->accuracy - temp_exp - 1;
}

void trim_extra_zero(long double* frac_part, parametrs* param) {
  if (param->spec_g && !param->hash) {
    if (!*frac_part) param->accuracy = 0;
    if (param->accuracy) {
      while (!(int)(*frac_part - floorl(*frac_part / 10.0L) * 10)) {
        *frac_part /= 10.0L;
        param->accuracy--;
      }
    }
  }
}