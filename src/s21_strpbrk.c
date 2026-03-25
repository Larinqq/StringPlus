#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *first_match = S21_NULL;

  for (; *str1 && first_match == S21_NULL; str1++) {
    if (s21_strchr(str2, *str1)) first_match = str1;
  }

  return (char *)first_match;
}