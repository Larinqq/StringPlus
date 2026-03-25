#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strlen_1) {
  const char *str = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_2_emty_str) {
  const char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_3_endstr) {
  const char *str = "1\0";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(memchr_1) {
  const char *str = "hello";
  int given_char = 'l';
  s21_size_t size = 3;
  ck_assert_pstr_eq(s21_memchr(str, given_char, size),
                    memchr(str, given_char, size));
}
END_TEST

START_TEST(memchr_2_emty_str) {
  const char *str = "";
  int given_char = 'l';
  s21_size_t size = 0;
  ck_assert_pstr_eq(s21_memchr(str, given_char, size),
                    memchr(str, given_char, size));
}
END_TEST

START_TEST(memchr_3_emty_given_char) {
  const char *str = "hell";
  int given_char = '\0';
  s21_size_t size = 3;
  ck_assert_pstr_eq(s21_memchr(str, given_char, size),
                    memchr(str, given_char, size));
}
END_TEST

START_TEST(memchr_4_emty_size) {
  const char *str = "hell0";
  int given_char = 'l';
  s21_size_t size = 0;
  ck_assert_pstr_eq(s21_memchr(str, given_char, size),
                    memchr(str, given_char, size));
}
END_TEST

START_TEST(memchr_5_first_char_match) {
  const char *str = "hello";
  int given_char = 'h';
  s21_size_t size = 5;
  ck_assert_pstr_eq(s21_memchr(str, given_char, size),
                    memchr(str, given_char, size));
}
END_TEST

START_TEST(memcmp_1) {
  const char *str1 = "hell0";
  const char *str2 = "hell0";
  s21_size_t size = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, size), memcmp(str1, str2, size));
}
END_TEST

START_TEST(memcmp_2_emty_str1) {
  const char *str1 = "                           ";
  const char *str2 = "hell0                             ";
  s21_size_t size = 25;
  ck_assert_int_eq(s21_memcmp(str1, str2, size), memcmp(str1, str2, size));
}
END_TEST

START_TEST(memcmp_3_emty_str2) {
  const char *str1 = "hell0                       ";
  const char *str2 = "                         ";
  s21_size_t size = 25;
  ck_assert_int_eq(s21_memcmp(str1, str2, size), memcmp(str1, str2, size));
}
END_TEST

START_TEST(memcmp_4_not_equal) {
  const char *str1 = "hddell04234132412341241234123414";
  const char *str2 = "hddell042341324123412412341234LLLL14";
  s21_size_t size = 25;
  ck_assert_int_eq(s21_memcmp(str1, str2, size), memcmp(str1, str2, size));
}
END_TEST

START_TEST(memcmp_5_not_equal_out_of_size) {
  const char *str1 = "hell0ewrwer";
  const char *str2 = "hell0";
  s21_size_t size = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, size), memcmp(str1, str2, size));
}
END_TEST

START_TEST(memcpy_1) {
  char str1[50] = "hell0ewrwer";
  const char *str2 = "12345678910";
  s21_size_t size = 10;
  ck_assert_str_eq(s21_memcpy(str1, str2, size), memcpy(str1, str2, size));
}
END_TEST

START_TEST(memcpy_2_emty_str1) {
  char str1[50] = "                    ";
  const char *str2 = "12345678910";
  s21_size_t size = 10;
  ck_assert_str_eq(s21_memcpy(str1, str2, size), memcpy(str1, str2, size));
}
END_TEST

START_TEST(memcpy_3_emty_str2) {
  char str1[50] = "        adsfasdfasdfasdf            ";
  const char *str2 = "              ";
  s21_size_t size = 10;
  ck_assert_str_eq(s21_memcpy(str1, str2, size), memcpy(str1, str2, size));
}
END_TEST

START_TEST(memcpy_4_spec_symbols) {
  char str1[50] = "   adsfasdfasdfasdf       ";
  const char *str2 = "  \t \0 \n       ";
  s21_size_t size = 15;
  ck_assert_str_eq(s21_memcpy(str1, str2, size), memcpy(str1, str2, size));
}
END_TEST

START_TEST(memset_1) {
  char str1[50] = "   adsfasdfasdfasdf       ";
  const char c = 'a';
  s21_size_t size = 15;
  ck_assert_str_eq(s21_memset(str1, c, size), memset(str1, c, size));
}
END_TEST

START_TEST(memset_2_empy_str1) {
  char str1[50] = "                     ";
  const char c = 'a';
  s21_size_t size = 15;
  ck_assert_str_eq(s21_memset(str1, c, size), memset(str1, c, size));
}
END_TEST

START_TEST(memset_3_empy_char) {
  char str1[50] = "  d ";
  const char c = ' ';
  s21_size_t size = 15;
  ck_assert_str_eq(s21_memset(str1, c, size), memset(str1, c, size));
}
END_TEST

START_TEST(memset_4_spec_char) {
  char str1[50] = "  d ";
  const char c = '\0';
  s21_size_t size = 15;
  ck_assert_str_eq(s21_memset(str1, c, size), memset(str1, c, size));
}
END_TEST

START_TEST(strcat_1) {
  char str1[50] = "  d ";
  char str2[50] = "asd  d ";
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

START_TEST(strcat_2_empty_str1) {
  char str1[50] = "     ";
  char str2[50] = "asd  d ";
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

START_TEST(strcat_3_empty_str2) {
  char str1[50] = "    sadadadfg;b 0 ";
  char str2[50] = " ";
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

START_TEST(strcat_4_spec_char) {
  char str1[50] = "    sa\tdadadfg;b 0 ";
  char str2[50] = "   \0";
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

START_TEST(strchr_1) {
  char str1[50] = "    sa\tdadadfg;b 0 ";
  char chr = 's';
  ck_assert_str_eq(s21_strchr(str1, chr), strchr(str1, chr));
}
END_TEST

START_TEST(strchr_2_empty_str1) {
  char str1[50] = "            ";
  char chr = 's';
  ck_assert_pstr_eq(s21_strchr(str1, chr), strchr(str1, chr));
}
END_TEST

START_TEST(strchr_3_empty_char) {
  char str1[50] = "            ";
  char chr = ' ';
  ck_assert_str_eq(s21_strchr(str1, chr), strchr(str1, chr));
}
END_TEST

START_TEST(strchr_4_spec_char) {
  char str1[50] = "   dasd         ";
  char chr = '\0';
  ck_assert_str_eq(s21_strchr(str1, chr), strchr(str1, chr));
}
END_TEST

START_TEST(strcmp_1) {
  char str1[50] = "123456789qwertyyuioooo";
  char str2[50] = "123456789qwertyyuioooo";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(strcmp_2_str1_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo33333333";
  char str2[50] = "123456789qwertyyuioooo";
  ck_assert_int_eq(s21_strcmp(str1, str2) > 0, strcmp(str1, str2) > 0);
}
END_TEST

START_TEST(strcmp_3_str2_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo";
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  ck_assert_int_eq(s21_strcmp(str1, str2) < 0, strcmp(str1, str2) < 0);
}
END_TEST

START_TEST(strcmp_4_str1_is_emty) {
  char str1[50] = "  ";
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  ck_assert_int_eq(s21_strcmp(str1, str2) < 0, strcmp(str1, str2) < 0);
}
END_TEST

START_TEST(strcmp_5_str2_is_emty) {
  char str1[50] = "123456789qwertyyuioooodsadasdasdasd";
  char str2[50] = "  ";
  ck_assert_int_eq(s21_strcmp(str1, str2) > 0, strcmp(str1, str2) > 0);
}
END_TEST

START_TEST(strcmp_6_str1_spec_char) {
  char str1[50] = "1234567\0 89qwertyyuioooodsadasdasdasd";
  char str2[50] = "1234567asdfasdfasdfsdf  ";
  ck_assert_int_eq(s21_strcmp(str1, str2) < 0, strcmp(str1, str2) < 0);
}
END_TEST

START_TEST(strcpy_1) {
  char str1[50] = "hell0ewrwer";
  const char *str2 = "12345678910";
  ck_assert_str_eq(s21_strcpy(str1, str2), strcpy(str1, str2));
}
END_TEST

START_TEST(strcpy_2_emty_str1) {
  char str1[50] = "                    ";
  const char *str2 = "12345678910";
  ck_assert_str_eq(s21_strcpy(str1, str2), strcpy(str1, str2));
}
END_TEST

START_TEST(strcpy_3_emty_str2) {
  char str1[50] = "        adsfasdfasdfasdf            ";
  const char *str2 = "              ";
  ck_assert_str_eq(s21_strcpy(str1, str2), strcpy(str1, str2));
}
END_TEST

START_TEST(strcpy_4_spec_symbols) {
  char str1[50] = "   adsfasdfasdfasdf       ";
  const char *str2 = "  \t \0 \n       ";
  ck_assert_str_eq(s21_strcpy(str1, str2), strcpy(str1, str2));
}
END_TEST

START_TEST(strcspn_1_equal) {
  char str1[50] = "123456789qwertyyuioooo";
  char str2[50] = "123456789qwertyyuioooo";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_2_str1_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo33333333";
  char str2[50] = "123456789qwertyyuioooo";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_3_str2_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo";
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_4_str1_is_emty) {
  char str1[50] = "  ";
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_5_str2_is_emty) {
  char str1[50] = "123456789qwertyyuioooodsadasdasdasd";
  char str2[50] = "  ";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_6_str1_spec_char) {
  char str1[50] = "1234567\0 89qwertyyuioooodsadasdasdasd";
  char str2[50] = "1234567asdfasdfasdfsdf  ";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strncat_1) {
  char str1[50] = "asd  d ";
  char str2[50] = "asd  d ";
  s21_size_t bytes = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, bytes), strncat(str1, str2, bytes));
}
END_TEST

START_TEST(strncat_2_empty_str1) {
  char str1[50] = "        ";
  char str2[50] = "asd          d ";
  s21_size_t bytes = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, bytes), strncat(str1, str2, bytes));
}
END_TEST

START_TEST(strncat_3_empty_str2) {
  char str1[50] = "    sadadadfg;b 0 ";
  char str2[50] = "       ";
  s21_size_t bytes = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, bytes), strncat(str1, str2, bytes));
}
END_TEST

START_TEST(strncat_4_spec_char) {
  char str1[50] = "    sa\tdadadfg;b 0 ";
  char str2[50] = "       \0";
  s21_size_t bytes = 10;
  ck_assert_str_eq(s21_strncat(str1, str2, bytes), strncat(str1, str2, bytes));
}
END_TEST

START_TEST(strncmp_1) {
  char str1[50] = "123456789qwertyyuioooo";
  char str2[50] = "123456789qwertyyuioooo";
  s21_size_t bytes = 10;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes), strncmp(str1, str2, bytes));
}
END_TEST

START_TEST(strncmp_2_str1_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo33333333";
  char str2[50] = "123456789qwertyyuioooo";
  s21_size_t bytes = 25;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes) > 0,

                   strncmp(str1, str2, bytes) > 0);
}
END_TEST

START_TEST(strncmp_3_str2_is_bigger) {
  char str1[50] = "123456789qwertyyuioooo";
  s21_size_t bytes = 25;
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes) < 0,
                   strncmp(str1, str2, bytes) < 0);
}
END_TEST

START_TEST(strncmp_4_str1_is_emty) {
  char str1[50] = "             ";
  char str2[50] = "123456789qwertyyuioooodsadasdasdasd";
  s21_size_t bytes = 10;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes) < 0,
                   strncmp(str1, str2, bytes) < 0);
}
END_TEST

START_TEST(strncmp_5_str2_is_emty) {
  char str1[50] = "123456789qwertyyuioooodsadasdasdasd";
  char str2[50] = "                ";
  s21_size_t bytes = 10;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes) > 0,
                   strncmp(str1, str2, bytes) > 0);
}
END_TEST

START_TEST(strncmp_6_str1_spec_char) {
  char str1[50] = "1234567\0 89qwertyyuioooodsadasdasdasd";
  char str2[50] = "1234567asdfasdfasdfsdf  ";
  s21_size_t bytes = 10;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes) < 0,
                   strncmp(str1, str2, bytes) < 0);
}
END_TEST

START_TEST(strncmp_7_str1_eq_short) {
  char str1[50] = "1234567\0 89qwertyyuioooodsadasdasdasd";
  char str2[50] = "1234567\0 89qwertyyuioooodsadasdasdasd";
  s21_size_t bytes = 8;
  ck_assert_int_eq(s21_strncmp(str1, str2, bytes), strncmp(str1, str2, bytes));
}
END_TEST

START_TEST(strncpy_1) {
  char str1[50] = "hell0ewrwer";
  const char *str2 = "12345678910";
  s21_size_t bytes = 8;
  ck_assert_str_eq(s21_strncpy(str1, str2, bytes), strncpy(str1, str2, bytes));
}
END_TEST

START_TEST(strncpy_2_emty_str1) {
  char str1[50] = "                    ";
  const char *str2 = "12345678910";
  s21_size_t bytes = 8;
  ck_assert_str_eq(s21_strncpy(str1, str2, bytes), strncpy(str1, str2, bytes));
}
END_TEST

START_TEST(strncpy_3_emty_str2) {
  char str1[50] = "        adsfasdfasdfasdf            ";
  const char *str2 = "              ";
  s21_size_t bytes = 8;
  ck_assert_str_eq(s21_strncpy(str1, str2, bytes), strncpy(str1, str2, bytes));
}
END_TEST

START_TEST(strncpy_4_spec_symbols) {
  char str1[50] = "   adsfasdfasdfasdf       ";
  const char *str2 = "  \t \0 \n       ";
  s21_size_t bytes = 8;
  ck_assert_str_eq(s21_strncpy(str1, str2, bytes), strncpy(str1, str2, bytes));
}
END_TEST

START_TEST(strpbrk_1) {
  const char str1[50] = "12334567890";
  const char str2[50] = "asddvg0";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_2_not_found) {
  const char str1[50] = "12334567890";
  const char str2[50] = "asddvg";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_3_spec_char) {
  const char str1[50] = "12334567890";
  const char str2[50] = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_4_emty_str1) {
  const char str1[50] = "                ";
  const char str2[50] = "adfqweerwtwfzv34q213adsf,m./,./''[]";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_5_emty_str2) {
  const char str1[50] = "adfqweerwtwfzv34q213ads f,m./,./''[] ";
  const char str2[50] = " ";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strrchr_1) {
  char str1[50] = "    sa\tdadbbbbbbbadfg;b 0 ";
  char chr = 'b';
  ck_assert_str_eq(s21_strrchr(str1, chr), strrchr(str1, chr));
}
END_TEST

START_TEST(strrchr_2_empty_str1) {
  char str1[50] = "            ";
  char chr = 's';
  ck_assert_pstr_eq(s21_strrchr(str1, chr), strrchr(str1, chr));
}
END_TEST

START_TEST(strrchr_3_empty_char) {
  char str1[50] = "      fsda     d ";
  char chr = ' ';
  ck_assert_str_eq(s21_strrchr(str1, chr), strrchr(str1, chr));
}
END_TEST

START_TEST(strrchr_4_spec_char) {
  char str1[50] = "   da\0sd         ";
  char chr = '\0';
  ck_assert_str_eq(s21_strrchr(str1, chr), strrchr(str1, chr));
}
END_TEST

START_TEST(strstr_1) {
  const char str1[50] = "1233abcd4567890";
  const char str2[50] = "abcd";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(strstr_2_not_found) {
  const char str1[50] = "1233abcd4567890";
  const char str2[50] = "llllllllll";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(strstr_3_spec_char) {
  const char str1[50] = "1233abcd4567890";
  const char str2[50] = "\0 abc";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(strstr_blabla) {
  const char str1[50] = "abc";
  const char str2[50] = "abcd";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(strtok_1) {
  char str1[] = "abc,dasdasd,asdasdasd,asdasdasdqweqwecxzcaeqwexcdasdqw,da";
  char str2[] = "abc,dasdasd,asdasdasd,asdasdasdqweqwecxzcaeqwexcdasdqw,da";
  char delim[] = ",";
  ck_assert_pstr_eq(strtok(str1, delim), s21_strtok(str2, delim));
}
END_TEST

START_TEST(strtok_2_null_in_delim) {
  char delim[] = ",";
  char str1[] = ",abc";

  char str2[] = ",abc";

  ck_assert_pstr_eq(strtok(str1, delim), s21_strtok(str2, delim));
}
END_TEST

START_TEST(strtok_3_no_delim_in_str) {
  char str1[] =
      "abc,dasdasd,asdasdasd,asdasdasdqweqwecxzcaeqwexcdasdqw,da,,jhgghg";
  char str2[] =
      "abc,dasdasd,asdasdasd,asdasdasdqweqwecxzcaeqwexcdasdqw,da,,jhgghg";
  char delim[] = ".";
  ck_assert_pstr_eq(strtok(str1, delim), s21_strtok(str2, delim));
}
END_TEST

START_TEST(strtok_4_emty_str) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = ".";
  ck_assert_pstr_eq(strtok(str1, delim), s21_strtok(str2, delim));
}
END_TEST

START_TEST(strtok_5_blabla) {
  char str1[] = "hello,world";
  char str2[] = "hello,world";
  char delim[] = ",";
  strtok(str1, delim);
  s21_strtok(str2, delim);
  strtok(NULL, delim);
  s21_strtok(NULL, delim);
  ck_assert_pstr_eq(strtok(NULL, delim), s21_strtok(NULL, delim));
}
END_TEST

START_TEST(strerror_1) {
  int error = 45;
  ck_assert_str_eq(s21_strerror(error), strerror(error));
}
END_TEST

START_TEST(strerror_2_out_of_range) {
  int error = 500;
  ck_assert_str_eq(s21_strerror(error), strerror(error));
}
END_TEST

START_TEST(strerror_3_negative) {
  int error = -1;
  ck_assert_str_eq(s21_strerror(error), strerror(error));
}
END_TEST

START_TEST(sprintf_1_nochar) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJndls";
  char nochar = ' ';
  s21_sprintf(s21_str, format, nochar);
  sprintf(str, format, nochar);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_2_add_char) {
  char s21_str[500] = "12345678asAdn";
  char str[500] = "91011121323abcd";
  char *format = "abcJ%c ndls";
  char c = '$';
  s21_sprintf(s21_str, format, c);
  sprintf(str, format, c);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_3_add_digit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%d ndl34s";
  int d = 900;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_4_add_digit_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%d ndl34s";
  int d = -900;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_5_add_idigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "12345678asdn";
  char *format = "abcJ%i ndls";
  int d = 900;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_6_add_idigit_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%i ndls";
  int d = -900;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_7_add_edigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%e ndlA6700000s";
  double d = 10e50;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_8_add_edigit_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%e ndlA6700000s";
  double d = -10e50;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_9_add_Edigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%E ndlA6700000s";
  double d = 10E50;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_10_add_Edigit_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%E ndlA6700000s";
  double d = -10E50;
  s21_sprintf(s21_str, format, d);
  sprintf(str, format, d);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_11_add_float) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = 10.91;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_12_add_float_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = -10.91;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_12_1_add_float_no_frac_part) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = 10.0;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_13_add_float_no_int_part) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = 0.999;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_14_add_float_endless_frac_part) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = 1.0 / 3;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_15_add_float_integer) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%f ndlA6700000s";
  double f = 10;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_16_add_gfloat) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ  |%g| ndlA6700000s";
  double f = 0.1234567890123345;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_17_add_gfloat_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ%g ndlA6700000s";
  double f = -0.1234567890123345;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_18_add_Gfloat) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%G| ndlA6700000s";
  double f = 0.1234567890123345;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_19_add_Gfloat_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%G| ndlA6700000s";
  double f = -0.1234567890123345;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_20_add_Gfloat_infnan) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%G %G %g %g| ndlA6700000s";
  double f = 1.0 / 0.0;
  double fu = 0.0 / 0.0;
  s21_sprintf(s21_str, format, f, fu, f, fu);
  sprintf(str, format, f, fu, f, fu);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_20_1_add_Gblabla) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%#LG %.*G %LG %LG %%| ndlA6700000s";
  long double f = 2.0L;
  double f_f = 0.2;
  long double fu = 0.20L;
  long double fuu = 0.0000004L;
  s21_sprintf(s21_str, format, f, 0, f_f, fu, fuu);
  sprintf(str, format, f, 0, f_f, fu, fuu);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_20_2_add_Gblabla) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "%g %Lg %g %#.0Lf %#o";
  double f = 1234567899.1;
  long double fu = 0.0L;
  double fi = 123.00;
  long double fo = 123.00L;
  unsigned int foo = -123;
  s21_sprintf(s21_str, format, f, fu, fi, fo, foo);
  sprintf(str, format, f, fu, fi, fo, foo);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_20_3_Branches) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "%#o %#o %o %o %#x %#X %x %x %x %hd %ld";
  s21_sprintf(s21_str, format, 123, 0, 123, -123, 255, 255, -255, 123, -123,
              123, -123);
  sprintf(str, format, 123, 0, 123, -123, 255, 255, -255, 123, -123, 123, -123);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_20_4_Branches) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *a = NULL;
  char *format = "%s %.3s %+ d %+.5d % d %d %+d %+o %x";
  s21_sprintf(s21_str, format, a, a, 123, -123, 456, -456, 0, 0755, 0xFF);
  sprintf(str, format, a, a, 123, -123, 456, -456, 0, 0755, 0xFF);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_21_add_Gfloat_no_pracpart) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%G| ndlA6700000s";
  double f = 40.0;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_22_add_odigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%o| ndlA6700000s";
  int f = 255;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_23_add_odigit_negative) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%o| ndlA6700000s";
  int f = -1;
  s21_sprintf(s21_str, format, f);
  sprintf(str, format, f);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_24_add_string) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%s| ndlA6700000s";
  char *s = "2133666uuhhehejdN&*  jdi";
  s21_sprintf(s21_str, format, s);
  sprintf(str, format, s);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_25_add_string_with_spec_chars) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%s| ndlA6700000s";
  char *s = "2133666uuhhehejdN&* \t  \njdi\0 sadasdasd23";
  s21_sprintf(s21_str, format, s);
  sprintf(str, format, s);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_26_add_udigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%u| ndlA6700000s";
  unsigned int u = 4294967295;
  s21_sprintf(s21_str, format, u);
  sprintf(str, format, u);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_27_add_xdigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%x| ndlA6700000s";
  unsigned int x = 0xDEADBEEF;
  s21_sprintf(s21_str, format, x);
  sprintf(str, format, x);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_28_add_Xdigit) {
  char s21_str[500] = "12345678asdn";
  char str[500] = "910111213abcd";
  char *format = "abcJ |%X| ndlA6700000s";
  unsigned int x = 0xCAFE;
  s21_sprintf(s21_str, format, x);
  sprintf(str, format, x);
  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_29_ptr) {
  char s21_str[50] = {0};
  char str[50] = {0};

  char *format = "%p";
  ck_assert_int_eq(s21_sprintf(s21_str, format, format),
                   sprintf(str, format, format));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_30_ptr_width) {
  char s21_str[50] = {0};
  char str[50] = {0};

  char *format = "%20p";
  ck_assert_int_eq(s21_sprintf(s21_str, format, format),
                   sprintf(str, format, format));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_31_ptr_null) {
  char s21_str[50] = {0};
  char str[50] = {0};

  char *format = "%p";
  char *ptr = NULL;
  ck_assert_int_eq(s21_sprintf(s21_str, format, ptr),
                   sprintf(str, format, ptr));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_32_ptr_minus_width) {
  char s21_str[50] = {0};
  char str[50] = {0};

  char *format = "%-*p";
  ck_assert_int_eq(s21_sprintf(s21_str, format, -20, format),
                   sprintf(str, format, -20, format));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_33_xX) {
  char s21_str[50] = {0};
  char str[50] = {0};
  unsigned int digit = 12;
  unsigned long int digit2 = 12345678910;
  char *format = "%x %hx %lX";
  ck_assert_int_eq(s21_sprintf(s21_str, format, digit, digit, digit2),
                   sprintf(str, format, digit, digit, digit2));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_34_xX) {
  char s21_str[50] = {0};
  char str[50] = {0};
  unsigned int digit = 12;
  unsigned int digit2 = 0;
  unsigned long int digit3 = 12345678910;
  char *format = "%6x %06hx %6lX";
  ck_assert_int_eq(s21_sprintf(s21_str, format, digit, digit2, digit3),
                   sprintf(str, format, digit, digit2, digit3));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_35_xX) {
  char s21_str[50] = {0};
  char str[50] = {0};
  unsigned int digit = 12;
  unsigned long int digit2 = 12345678910;
  char *format = "%.*x %.4hx %.4lX";
  ck_assert_int_eq(s21_sprintf(s21_str, format, 4, digit, digit, digit2),
                   sprintf(str, format, 4, digit, digit, digit2));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_36_xX) {
  char s21_str[50] = {0};
  char str[50] = {0};
  unsigned int digit = 12;
  unsigned long int digit2 = 12345678910;
  char *format = "%-#4x %#4.4hx %#lX";
  ck_assert_int_eq(s21_sprintf(s21_str, format, digit, digit, digit2),
                   sprintf(str, format, digit, digit, digit2));

  ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(to_upper_1) {
  char *str = "hElLo worlD1!{}";
  void *str2 = s21_to_upper(str);
  ck_assert_str_eq(str2, "HELLO WORLD1!{}");
  free(str2);
}
END_TEST

START_TEST(to_upper_2_empty) {
  char *str = "";
  void *str2 = s21_to_upper(str);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_upper_3_all_up) {
  char *str = "HELLO";
  void *str2 = s21_to_upper(str);
  ck_assert_str_eq(str2, "HELLO");
  free(str2);
}
END_TEST

START_TEST(to_upper_4_null) {
  char *str = S21_NULL;
  void *str2 = s21_to_upper(str);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}

END_TEST

START_TEST(to_lower_1) {
  char *str = "hElLo worlD1!";
  void *str2 = s21_to_lower(str);
  ck_assert_str_eq(str2, "hello world1!");
  free(str2);
}
END_TEST

START_TEST(to_lower_2_empty) {
  char *str = "";
  void *str2 = s21_to_lower(str);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_lower_3_all_low) {
  char *str = "hello";
  void *str2 = s21_to_lower(str);
  ck_assert_str_eq(str2, "hello");
  free(str2);
}
END_TEST

START_TEST(to_lower_4_null) {
  char *str = S21_NULL;
  void *str2 = s21_to_lower(str);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(insert_1) {
  char *str = "HelloWorld";
  void *str2 = s21_insert(str, ", ", 5);
  ck_assert_str_eq(str2, "Hello, World");
  free(str2);
}
END_TEST

START_TEST(insert_2_empty) {
  char *str = "";
  void *str2 = s21_insert(str, "", 0);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(insert_3_zero_index) {
  char *str = "case";
  void *str2 = s21_insert(str, "Test ", 0);
  ck_assert_str_eq(str2, "Test case");
  free(str2);
}
END_TEST

START_TEST(insert_4_null) {
  char *str = "case";
  void *str2 = s21_insert(str, "Test ", 25);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(insert_5_src_null) {
  char *str = S21_NULL;
  void *str2 = s21_insert(str, "Test ", 0);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(insert_6_str_null) {
  char *str = "case";
  void *str2 = s21_insert(str, S21_NULL, 0);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(trim_1) {
  char *str = "***Hello*World***";
  void *str2 = s21_trim(str, "*");
  ck_assert_str_eq(str2, "Hello*World");
  free(str2);
}
END_TEST

START_TEST(trim_2_empty) {
  char *str = "";
  void *str2 = s21_trim(str, "*");
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(trim_3_delete_all) {
  char *str = "******";
  void *str2 = s21_trim(str, "*");
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(trim_4_src_null) {
  char *str = S21_NULL;
  void *str2 = s21_trim(str, "*");
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(trim_5_trim_chars_null) {
  char *str = "***Hello*World***";
  void *str2 = s21_trim(str, S21_NULL);
  ck_assert_str_eq(str2, "***Hello*World***");
  free(str2);
}
END_TEST

Suite *stringSuite(void) {
  Suite *stringTestSuite;
  TCase *tcCore;

  stringTestSuite = suite_create("Basic_tests");
  tcCore = tcase_create("Core");

  tcase_add_test(tcCore, strlen_1);
  tcase_add_test(tcCore, strlen_2_emty_str);
  tcase_add_test(tcCore, strlen_3_endstr);

  tcase_add_test(tcCore, memchr_1);
  tcase_add_test(tcCore, memchr_2_emty_str);
  tcase_add_test(tcCore, memchr_3_emty_given_char);
  tcase_add_test(tcCore, memchr_4_emty_size);
  tcase_add_test(tcCore, memchr_5_first_char_match);

  tcase_add_test(tcCore, memcmp_1);
  tcase_add_test(tcCore, memcmp_2_emty_str1);
  tcase_add_test(tcCore, memcmp_3_emty_str2);
  tcase_add_test(tcCore, memcmp_4_not_equal);
  tcase_add_test(tcCore, memcmp_5_not_equal_out_of_size);

  tcase_add_test(tcCore, memcpy_1);
  tcase_add_test(tcCore, memcpy_2_emty_str1);
  tcase_add_test(tcCore, memcpy_3_emty_str2);
  tcase_add_test(tcCore, memcpy_4_spec_symbols);

  tcase_add_test(tcCore, memset_1);
  tcase_add_test(tcCore, memset_2_empy_str1);
  tcase_add_test(tcCore, memset_3_empy_char);
  tcase_add_test(tcCore, memset_4_spec_char);

  tcase_add_test(tcCore, strcat_1);
  tcase_add_test(tcCore, strcat_2_empty_str1);
  tcase_add_test(tcCore, strcat_3_empty_str2);
  tcase_add_test(tcCore, strcat_4_spec_char);

  tcase_add_test(tcCore, strchr_1);
  tcase_add_test(tcCore, strchr_2_empty_str1);
  tcase_add_test(tcCore, strchr_3_empty_char);
  tcase_add_test(tcCore, strchr_4_spec_char);

  tcase_add_test(tcCore, strcmp_1);
  tcase_add_test(tcCore, strcmp_2_str1_is_bigger);
  tcase_add_test(tcCore, strcmp_3_str2_is_bigger);
  tcase_add_test(tcCore, strcmp_4_str1_is_emty);
  tcase_add_test(tcCore, strcmp_5_str2_is_emty);
  tcase_add_test(tcCore, strcmp_6_str1_spec_char);

  tcase_add_test(tcCore, strcpy_1);
  tcase_add_test(tcCore, strcpy_2_emty_str1);
  tcase_add_test(tcCore, strcpy_3_emty_str2);
  tcase_add_test(tcCore, strcpy_4_spec_symbols);

  tcase_add_test(tcCore, strcspn_1_equal);
  tcase_add_test(tcCore, strcspn_2_str1_is_bigger);
  tcase_add_test(tcCore, strcspn_3_str2_is_bigger);
  tcase_add_test(tcCore, strcspn_4_str1_is_emty);
  tcase_add_test(tcCore, strcspn_5_str2_is_emty);
  tcase_add_test(tcCore, strcspn_6_str1_spec_char);

  tcase_add_test(tcCore, strncat_1);
  tcase_add_test(tcCore, strncat_2_empty_str1);
  tcase_add_test(tcCore, strncat_3_empty_str2);
  tcase_add_test(tcCore, strncat_4_spec_char);

  tcase_add_test(tcCore, strncmp_1);
  tcase_add_test(tcCore, strncmp_2_str1_is_bigger);
  tcase_add_test(tcCore, strncmp_3_str2_is_bigger);
  tcase_add_test(tcCore, strncmp_4_str1_is_emty);
  tcase_add_test(tcCore, strncmp_5_str2_is_emty);
  tcase_add_test(tcCore, strncmp_6_str1_spec_char);
  tcase_add_test(tcCore, strncmp_7_str1_eq_short);

  tcase_add_test(tcCore, strncpy_1);
  tcase_add_test(tcCore, strncpy_2_emty_str1);
  tcase_add_test(tcCore, strncpy_3_emty_str2);
  tcase_add_test(tcCore, strncpy_4_spec_symbols);

  tcase_add_test(tcCore, strpbrk_1);
  tcase_add_test(tcCore, strpbrk_2_not_found);
  tcase_add_test(tcCore, strpbrk_3_spec_char);
  tcase_add_test(tcCore, strpbrk_4_emty_str1);
  tcase_add_test(tcCore, strpbrk_5_emty_str2);

  tcase_add_test(tcCore, strrchr_1);
  tcase_add_test(tcCore, strrchr_2_empty_str1);
  tcase_add_test(tcCore, strrchr_3_empty_char);
  tcase_add_test(tcCore, strrchr_4_spec_char);

  tcase_add_test(tcCore, strstr_1);
  tcase_add_test(tcCore, strstr_2_not_found);
  tcase_add_test(tcCore, strstr_3_spec_char);
  tcase_add_test(tcCore, strstr_blabla);

  tcase_add_test(tcCore, strtok_1);
  tcase_add_test(tcCore, strtok_2_null_in_delim);
  tcase_add_test(tcCore, strtok_3_no_delim_in_str);
  tcase_add_test(tcCore, strtok_4_emty_str);
  tcase_add_test(tcCore, strtok_5_blabla);

  tcase_add_test(tcCore, strerror_1);
  tcase_add_test(tcCore, strerror_2_out_of_range);
  tcase_add_test(tcCore, strerror_3_negative);

  tcase_add_test(tcCore, sprintf_1_nochar);
  tcase_add_test(tcCore, sprintf_2_add_char);
  tcase_add_test(tcCore, sprintf_3_add_digit);
  tcase_add_test(tcCore, sprintf_4_add_digit_negative);
  tcase_add_test(tcCore, sprintf_5_add_idigit);
  tcase_add_test(tcCore, sprintf_6_add_idigit_negative);
  tcase_add_test(tcCore, sprintf_7_add_edigit);
  tcase_add_test(tcCore, sprintf_8_add_edigit_negative);
  tcase_add_test(tcCore, sprintf_9_add_Edigit);
  tcase_add_test(tcCore, sprintf_10_add_Edigit_negative);
  tcase_add_test(tcCore, sprintf_11_add_float);
  tcase_add_test(tcCore, sprintf_12_add_float_negative);
  tcase_add_test(tcCore, sprintf_12_1_add_float_no_frac_part);
  tcase_add_test(tcCore, sprintf_13_add_float_no_int_part);
  tcase_add_test(tcCore, sprintf_14_add_float_endless_frac_part);
  tcase_add_test(tcCore, sprintf_15_add_float_integer);
  tcase_add_test(tcCore, sprintf_16_add_gfloat);
  tcase_add_test(tcCore, sprintf_17_add_gfloat_negative);
  tcase_add_test(tcCore, sprintf_18_add_Gfloat);
  tcase_add_test(tcCore, sprintf_19_add_Gfloat_negative);
#ifndef VALGRIND
  tcase_add_test(tcCore, sprintf_20_add_Gfloat_infnan);
#endif
  tcase_add_test(tcCore, sprintf_20_1_add_Gblabla);
  tcase_add_test(tcCore, sprintf_20_2_add_Gblabla);
  tcase_add_test(tcCore, sprintf_20_3_Branches);
  tcase_add_test(tcCore, sprintf_20_4_Branches);
  tcase_add_test(tcCore, sprintf_21_add_Gfloat_no_pracpart);
  tcase_add_test(tcCore, sprintf_22_add_odigit);
  tcase_add_test(tcCore, sprintf_23_add_odigit_negative);
  tcase_add_test(tcCore, sprintf_24_add_string);
  tcase_add_test(tcCore, sprintf_25_add_string_with_spec_chars);
  tcase_add_test(tcCore, sprintf_26_add_udigit);
  tcase_add_test(tcCore, sprintf_27_add_xdigit);
  tcase_add_test(tcCore, sprintf_28_add_Xdigit);
  tcase_add_test(tcCore, sprintf_29_ptr);
  tcase_add_test(tcCore, sprintf_30_ptr_width);
  tcase_add_test(tcCore, sprintf_31_ptr_null);
  tcase_add_test(tcCore, sprintf_32_ptr_minus_width);
  tcase_add_test(tcCore, sprintf_33_xX);
  tcase_add_test(tcCore, sprintf_34_xX);
  tcase_add_test(tcCore, sprintf_35_xX);
  tcase_add_test(tcCore, sprintf_36_xX);

  tcase_add_test(tcCore, to_upper_1);
  tcase_add_test(tcCore, to_upper_2_empty);
  tcase_add_test(tcCore, to_upper_3_all_up);
  tcase_add_test(tcCore, to_upper_4_null);

  tcase_add_test(tcCore, to_lower_1);
  tcase_add_test(tcCore, to_lower_2_empty);
  tcase_add_test(tcCore, to_lower_3_all_low);
  tcase_add_test(tcCore, to_lower_4_null);

  tcase_add_test(tcCore, insert_1);
  tcase_add_test(tcCore, insert_2_empty);
  tcase_add_test(tcCore, insert_3_zero_index);
  tcase_add_test(tcCore, insert_4_null);
  tcase_add_test(tcCore, insert_5_src_null);
  tcase_add_test(tcCore, insert_6_str_null);

  tcase_add_test(tcCore, trim_1);
  tcase_add_test(tcCore, trim_2_empty);
  tcase_add_test(tcCore, trim_3_delete_all);
  tcase_add_test(tcCore, trim_4_src_null);
  tcase_add_test(tcCore, trim_5_trim_chars_null);

  suite_add_tcase(stringTestSuite, tcCore);

  return stringTestSuite;
}

int main() {
  int failed_counter = 0;
  Suite *stringTestSuite;
  SRunner *suiteRunner;

  stringTestSuite = stringSuite();
  suiteRunner = srunner_create(stringTestSuite);
  srunner_set_fork_status(suiteRunner, CK_NOFORK);
  srunner_run_all(suiteRunner, CK_NORMAL);

  failed_counter = srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  return (failed_counter == 0) ? 0 : 1;
}