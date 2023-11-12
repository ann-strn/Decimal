CC=gcc
FLAGS=-g -Wall -Wextra -Werror -std=c11
TEST_FLAGS=-lcheck -lpthread -pthread -lm 
TEST = tests/test
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

TEST_SRC = $(wildcard $(TEST)*.c)
TEST_OBJ = $(patsubst $(TEST)%.c, $(TEST)%.o, $(TEST_SRC))

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lsubunit -lgcov -lrt
endif

all: decimal.a

decimal.a: $(OBJ)
	ar rc decimal.a $^
	ranlib decimal.a

test.a: $(TEST_OBJ)
	ar rc $(TEST).a $^
	ranlib $(TEST).a

covered:
	$(CC) $(FLAGS) -c $(SRC) --coverage
	ar rc decimal.a $(OBJ)
	ranlib decimal.a

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format
	
test: clean covered test.a
	$(CC) $(FLAGS) --coverage -o $(TEST).o $(TEST).c -c
	$(CC) $(TEST).o $(TEST).a decimal.a -o $(TEST) --coverage $(FLAGS) $(TEST_FLAGS)
	./$(TEST)

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=yes  ./$(TEST)
else
	leaks --atExit -- ./$(TEST)
endif

clean:
	rm -rf *.o *.a *.gcda *.gcno *.gcov *.info *.html $(TEST)*.gcda $(TEST)*.gcno $(TEST)*.o $(TEST)*.a $(TEST) gcov_report

rebuild: clean all

gcov_report: test
	lcov -t "decimal" -o decimal.info -c -d .
	genhtml -o gcov_report decimal.info