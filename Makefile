CC = g++
SRC = s21_matrix_oop.cpp
OBJ = s21_matrix_oop.o
OBJ_TEST = s21_matrix_test.o
LIB = s21_matrix_oop.a
FLAGS= -Wall -Werror -Wextra -std=c++20
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage
TESTFLAGS= -pthread -lgtest
CHECK_FLAG = -lstdc++
SUDO = sudo apt-get install

REPORT_DIR = report

UNAME_S = $(shell uname)
ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
endif
ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
endif

all: clean test

s21_matrix_oop.a:
	$(CC) -c $(FLAGS) $(SRC) -o $(OBJ)
	ar -rcs $(LIB) $(OBJ)
	ranlib $(LIB)
	rm -rf *.o

test: $(LIB)
	$(CC) $(FLAGS) -c test.cpp -o test.o
	$(CC) $(FLAGS) $(CHECK_FLAG) test.o $(LIB) $(TESTFLAGS) -o test.out
	rm -rf *.o
	./test.out

gcov_report: FLAGS += $(GCOVFLAGS)
gcov_report: clean test
	@mkdir -p $(REPORT_DIR)/gcov

	@lcov -c -d . -o $(REPORT_DIR)/gcov/coverage.info --rc lcov_branch_coverage=1 --ignore-errors mismatch
	@lcov --remove $(REPORT_DIR)/gcov/coverage.info "/usr/*" -o $(REPORT_DIR)/gcov/coverage_tmp.info  --ignore-errors unused
	@lcov --remove $(REPORT_DIR)/gcov/coverage_tmp.info "*/c++/*" -o $(REPORT_DIR)/gcov/coverage.info --ignore-errors unused
	@rm -f $(REPORT_DIR)/gcov/coverage_tmp.info
	@genhtml $(REPORT_DIR)/gcov/coverage.info --output-directory $(REPORT_DIR)/gcov/report --no-branch-coverage

clean:
	@rm -rf *.out *.o *.gcno *.info *.gcda *.a *.o
	@rm -rf $(REPORT_DIR)
	@rm -rf build

clang_format:
	@find . -name '*.h' -o -name '*.cpp' | xargs clang-format -style=Google -i

clang_check:
	@find . -name '*.h' -o -name '*.cpp'| xargs clang-format -style=Google -n

cpp_check:
	@find . -name '*.h' -o -name '*.cpp'| xargs cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedStructMember --std=c++20 --language=c++

gdb:
	$(CC) -c -g $(FLAGS) $(SRC) -o $(OBJ)
	ar -rcs $(LIB) $(OBJ)
	ranlib $(LIB)
	rm -rf *.o
	$(CC) $(FLAGS) -g -c test.cpp -o test.o
	$(CC) $(FLAGS) $(CHECK_FLAG) test.o $(LIB) $(TESTFLAGS) -o test.out
	rm -rf *.o
	gdb ./test.out

gtest:
	@$(SUDO) libgtest-dev libgmock-dev
	@$(SUDO) libtbb-dev
	@$(SUDO) cmake
	@cd /usr/src/googletest/
	@sudo mkdir build && cd build
	@sudo cmake ..
	@sudo make
	@sudo cp lib/* /usr/lib