#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int shift = 0;

  while (dest[shift] != '\0') {
    shift++;
  }

  for (s21_size_t i = 0; i < n; i++) {
    dest[i + shift] = src[i];
  }

  return dest;
}