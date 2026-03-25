#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  int skip_cycle = 0;

  for (s21_size_t i = 0; !skip_cycle; i++) {
    if (src[i] != '\0')
      dest[i] = src[i];
    else {
      dest[i] = '\0';
      skip_cycle = 1;
    }
  }
  return dest;
}