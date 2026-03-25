#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;
  char *token_start = S21_NULL;
  int found = 0;

  if (str == S21_NULL) str = next_token;
  if (str != S21_NULL) {
    while (*str != '\0' && s21_strchr(delim, *str) != S21_NULL) str++;

    if (*str != '\0') {
      token_start = str;
      str = s21_strpbrk(token_start, delim);
      found = 1;
      if (str != S21_NULL) {
        *str = '\0';
        next_token = str + 1;
      } else
        next_token = S21_NULL;
    }
  }
  return found ? token_start : S21_NULL;
}