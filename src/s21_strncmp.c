#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int difference = 0;
  int skip_cycle = 0;

  for (s21_size_t i = 0; i < n && !skip_cycle; i++) {
    if (str1[i] != str2[i]) {
      difference = str1[i] - str2[i];
      skip_cycle = 1;
    }
    if ((str1[i] == '\0') && !skip_cycle) {
      difference = 0;
      skip_cycle = 1;
    }
  }
  return difference;
}