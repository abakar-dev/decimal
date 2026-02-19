OBJS = getAndSet.o checker.o otherFun.o arithmetic.o comparison.o convertors.o additionalFunc.o

GCOV = -fprofile-arcs -ftest-coverage

CFLAGS = -Wall -Wextra -Werror


all :  #-- будет все собирать, но не запускать
	make rebuild
	make -C ./tests rebuild



s21_decimal.a: $(OBJS)
	ar rcs $@ $^ 


%.o : %.c
	gcc $(CFLAGS) -c $< -o $@ 


s21_decimal_gcov.a: $(OBJS:.o=.gcov.o)
	ar rcs $@ $^

%.gcov.o: %.c
	gcc $(CFLAGS) $(GCOV) -c $< -o $@

test :  #-- Собирает все и запускает с без отчета для тестов
	make all
	make exe_for_test_create
	./run_tests.exe


exe_for_test_create : ./tests/main.c ./tests/s21_decimal_test.a ./s21_decimal.a
	gcc -o run_tests.exe ./tests/main.c ./tests/s21_decimal_test.a ./s21_decimal.a -lcheck -lm -lsubunit

exe_for_test_create_gcov : ./tests/main.c ./tests/s21_decimal_test.a ./s21_decimal_gcov.a
	gcc -o run_tests.exe ./tests/main.c ./tests/s21_decimal_test.a ./s21_decimal_gcov.a -lcheck -lm -lsubunit $(GCOV)

run_tests:
	./run_tests.exe


gcov_report:
	make all
	make exe_for_test_create_gcov
	make run_tests
	gcovr -r . --html --html-details -o ./gcov_report.html



rebuild :
	make clean
	make s21_decimal.a

clean : 
	rm -f *.o *.a *.exe *.gcno *.gcda *.html *.css
	make -C ./tests clean




clang-checker :
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n tests/*.c
	clang-format -n tests/*.h
	clang-format -n tests/arithmetic/*



clang-formater :
	clang-format -i *.c
	clang-format -i *.h
	clang-format -i tests/*.c
	clang-format -i tests/*.h
	clang-format -i tests/arithmetic/*
