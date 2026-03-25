#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int len = s21_strlen(str);
  const char *res = S21_NULL;

  for (int i = 0; i <= len && res == S21_NULL; i++) {
    if (str[i] == c) res = (str + i);
  }
  return (char *)res;
}
