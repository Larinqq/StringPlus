#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *innerSrc = (unsigned char *)src;

  unsigned char *innerDest = (unsigned char *)dest;

  for (s21_size_t i = 0; i < n; i++) {
    innerDest[i] = innerSrc[i];
  }

  return dest;
}