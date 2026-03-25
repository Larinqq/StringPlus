#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  const char* temp = str;
  while (*temp) temp++;
  return (s21_size_t)(temp - str);
}