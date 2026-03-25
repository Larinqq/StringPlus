#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sprintf.h"
#include "s21_string.h"

int main() {
  char str1[5000] = "text in string";
  char strs[50000] = "text in string 2";
  char *str2 = "345";
  float fl = 1234.999999999999;
  s21_sprintf(str1, "s->|%s| format string  f-> |% 50.0f|", str2, fl);
  sprintf(strs, "s->|%s| format string  f-> |% 50.0f|", str2, fl);
  printf("my %s\n", str1);
  printf("or %s\n", strs);
  return 0;
}
