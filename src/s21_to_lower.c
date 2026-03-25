#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  } else {
    s21_size_t length = s21_strlen(str);

    char *answer = (char *)malloc(length + 1);
    answer[0] = '\0';

    for (int i = 0; i < (int)length; i++) {
      if ((str[i] >= 65) && (str[i] <= 90)) {
        answer[i] = str[i] + 32;
      } else {
        answer[i] = str[i];
      }
    }

    answer[length] = '\0';

    return answer;
  }
}