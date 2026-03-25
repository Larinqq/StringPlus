#include "s21_string.h"

char* s21_strcat(char* dest, char* src) {
  s21_size_t destLenght = s21_strlen(dest);
  s21_size_t srcLenght = s21_strlen(src);
  for (s21_size_t i = 0; i <= srcLenght; i++) {
    dest[destLenght + i] = src[i];
  }
  return dest;
}
