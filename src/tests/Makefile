CFLAGS = -Wall -Wextra -Werror
TEST_OBJS = \
    ./arithmetic/add_test.o ./arithmetic/sub_test.o ./arithmetic/mul_test.o ./arithmetic/div_test.o ./other_test.o


# Цель для сборки библиотеки тестов
s21_decimal_test.a: $(TEST_OBJS)
	ar rcs $@ $^

# Правила для объектных файлов тестов
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@


# Команды
rebuild :
	make clean
	make s21_decimal_test.a

assemble :
	make rebuild
	rm -f *.o ./arithmetic/*.o

clean :
	rm -f *.o *.a */*.gcda */*.gcno *.gcda *.gcno
	rm -f ./arithmetic/*.o
