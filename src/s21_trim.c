#include <stdlib.h>

#include "s21_string.h"

int isContain(char c, const char *trimChars);

void *s21_trim(const char *src, const char *trim_chars) {
  const char *default_trim_chars = " \t\n\r\f\v";
  if (src == S21_NULL) {
    return S21_NULL;
  }

  const char *chars_to_trim = (trim_chars == S21_NULL || *trim_chars == '\0')
                                  ? default_trim_chars
                                  : trim_chars;

  s21_size_t length = s21_strlen(src);

  int beginIndex = 0;
  int endIndex = s21_strlen(src) - 1;

  int iterator = 0;

  while (isContain(src[iterator], chars_to_trim) == 1) {
    beginIndex++;
    iterator++;
  }

  iterator = s21_strlen(src) - 1;

  while (isContain(src[iterator], chars_to_trim) == 1) {
    endIndex--;
    iterator--;
  }

  char *answer = (char *)malloc(length + 1);
  answer[0] = '\0';
  int answerCounter = 0;
  for (int i = 0; i < (int)s21_strlen(src); i++) {
    if ((isContain(src[i], chars_to_trim) == 0) ||
        ((i > beginIndex) && (i < endIndex))) {
      answer[answerCounter] = src[i];
      answerCounter++;
    }
  }

  answer[answerCounter] = '\0';
  return answer;
}

int isContain(char c, const char *trimChars) {
  int isContain = 0;
  for (int i = 0; i < (int)s21_strlen(trimChars); i++) {
    if (trimChars[i] == c) {
      isContain = 1;
    }
  }

  return isContain;
}