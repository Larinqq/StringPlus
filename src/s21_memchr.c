#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  unsigned char uc = (unsigned char)c;
  void *answer = S21_NULL;
  int skip = 0;

  for (s21_size_t i = 0; i < n && !skip; i++) {
    if (p[i] == uc) {
      answer = (void *)(p + i);
      skip = 1;
    }
  }
  return answer;
}