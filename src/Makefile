CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -lcheck -lm

SRCS = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strchr.c s21_strcspn.c  s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strstr.c s21_strtok.c s21_strcat.c s21_strcmp.c s21_strcpy.c s21_sprintf.c s21_strerror.c s21_to_lower.c s21_to_upper.c s21_trim.c s21_insert.c
HEADERS = s21_string.h 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    OPEN_COMMAND=xdg-open
	TESTFLAGS += -lsubunit
else
    OPEN_COMMAND=open
endif

OBJS = $(SRCS:.c=.o)


all: s21_string.a 

debug: s21_string.a debug.c
	$(CC) $(CFLAGS) debug.c s21_string.a -o a.out -lm
	rm -f $(OBJS)
	./a.out

s21_string.a: $(OBJS) $(HEADERS)
	ar rcs s21_string.a $(OBJS)
	ranlib s21_string.a

test: s21_string.a
	$(CC) $(CFLAGS) test_stringh.c s21_string.a -g -o test.out $(TESTFLAGS)
	./test.out
	
test_valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=./valgrind.log ./test.out
	$(OPEN_COMMAND) ./valgrind.log

gcov_report: clean test_stringh.c
	$(CC) $(GCOVFLAGS) $(SRCS) test_stringh.c -o report.out $(TESTFLAGS)
	./report.out
	lcov -t "report" -o coverage.info -c -d . --rc lcov_branch_coverage=1
	lcov --remove coverage.info "*test_stringh.c" -o filtered_coverage.info --rc lcov_branch_coverage=1
	genhtml -o ./gcov_report filtered_coverage.info --branch-coverage
	rm -f *.gcno *.gcda *.info report.out *.gcov $(OBJS)
	$(OPEN_COMMAND) ./gcov_report/index.html


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) s21_string.a a.out test.out report.out
	rm -f *.gcno *.gcda *.info *.gcov
	rm -rf gcov_report

rebuild: clean all

.PHONY: all clean rebuild test gcov_report test_build test_valgrind

