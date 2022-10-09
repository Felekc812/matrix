CFLAGS = -Wall -Werror -Wextra
SOURCE = $(wildcard s21_*.c)
OS=$(shell uname)
#SANIT = -g3 -fsanitize=address
ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm -lsubunit
else
  LIBS=-lcheck
endif

all: test gcov_report

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o: s21_matrix.c
	gcc -c s21_matrix.c

test: s21_matrix.o s21_matrix.a
	gcc $(SANIT) --coverage s21_test.c s21_matrix.c $(LIBS) $(CFLAGS)
	./a.out

gcov_report:
	rm -rf a-s21_matrix.gcda a-s21_matrix.gcno
	gcovr --html --html-details -o report.html
	
check: ${SOURCE}
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
	-python ../materials/linters/cpplint.py --extensions=c $^

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.html *.css
	rm -rf ./report

lcov:
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory ./

