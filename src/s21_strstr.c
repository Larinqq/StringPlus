#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  const char* match = S21_NULL;
  if (*needle == '\0')
    match = haystack;
  else {
    for (; *haystack != '\0' && match == S21_NULL; haystack++) {
      const char* h = haystack;
      const char* n = needle;
      while (*h != '\0' && *n != '\0' && *h == *n) {
        h++;
        n++;
      }
      if (*n == '\0') match = haystack;
    }
  }
  return (char*)match;
}