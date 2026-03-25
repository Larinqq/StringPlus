#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *last_match = S21_NULL;
  char ch = (char)c;
  do {
    if (*str == ch) last_match = str;
  } while (*str++);
  return (char *)last_match;
}