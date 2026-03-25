#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if ((src == S21_NULL) || (str == S21_NULL) ||
      (s21_strlen(src) < start_index)) {
    return S21_NULL;
  } else {
    s21_size_t length = s21_strlen(src) + s21_strlen(str);

    char *answer = (char *)malloc(length + 1);
    answer[0] = '\0';

    int srcCounter = 0;

    for (int i = 0; i < (int)length; i++) {
      if (i == (int)(start_index)) {
        for (int j = 0; j < (int)s21_strlen(str); j++) {
          answer[i + j] = str[j];
        }
        i = i + s21_strlen(str) - 1;
      } else {
        answer[i] = src[srcCounter];
        srcCounter++;
      }
    }

    answer[length] = '\0';

    return answer;
  }
}