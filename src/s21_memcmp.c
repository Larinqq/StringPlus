#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  unsigned const char* innerStr1 = str1;
  unsigned const char* innerStr2 = str2;

  int answer = 0;

  for (s21_size_t i = 0; i < n && answer == 0; i++) {
    if (innerStr1[i] != innerStr2[i]) {
      answer = innerStr1[i] - innerStr2[i];
    }
  }

  return answer;
}