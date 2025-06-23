#!/bin/bash
# minunit-setup.sh
# Script to set up MinUnit in any C project
# Author: Angello López Molina

set -e

# Check for include directory argument
if [ -z "$1" ]; then
    echo "Usage: $0 <include_dir>"
    echo "Example: $0 includes"
    exit 1
fi
INCLUDE_DIR="$1"

# Project base directory
BASE_DIR=$(pwd)

# Check if minunit.h or test directory already exists
if [ -f "$BASE_DIR/$INCLUDE_DIR/minunit.h" ]; then
    echo "minunit.h already exists in $INCLUDE_DIR."
elif [ -d "$BASE_DIR/test" ]; then
    echo "Warning: test/ directory already exists."
fi

# Check and create minunit.h if it does not exist
if [ ! -f "$BASE_DIR/$INCLUDE_DIR/minunit.h" ]; then
    mkdir -p "$BASE_DIR/$INCLUDE_DIR"
    cat > "$BASE_DIR/$INCLUDE_DIR/minunit.h" << 'EOF'
#ifndef MINUNIT_H
# define MINUNIT_H

# include <stdio.h>

# define MU_COLOR_GREEN "\033[0;32m"
# define MU_COLOR_RED   "\033[0;31m"
# define MU_COLOR_RESET "\033[0m"

# define MU_TEST(name) static char *name(void)
# define MU_TEST_SUITE(name) static void name(void)
# define MU_RUN_TEST(test) do { \
    char *message = test(); \
    tests_run++; \
    if (message) { \
        printf(MU_COLOR_RED "[KO] %s\n" MU_COLOR_RESET, message); \
    } else { \
        printf(MU_COLOR_GREEN "[OK] %s\n" MU_COLOR_RESET, #test); \
    } \
} while (0)
# define MU_RUN_SUITE(suite) suite()
# define MU_REPORT() printf("%d tests run\n", tests_run)

# define mu_assert(message, test) do { if (!(test)) return message; } while (0)

extern int tests_run;

char* all_tests();

#endif
EOF
    echo "✔ File $INCLUDE_DIR/minunit.h created."
else
    echo "✔ File $INCLUDE_DIR/minunit.h already exists."
fi

# Check and create test/ and test_dummy.c if not exist
if [ ! -d "$BASE_DIR/test" ]; then
    mkdir -p "$BASE_DIR/test"
    echo "✔ Directory test/ created."
fi
if [ ! -f "$BASE_DIR/test/test_dummy.c" ]; then
    cat > "$BASE_DIR/test/test_dummy.c" << EOF
#include "../$INCLUDE_DIR/minunit.h"

int tests_run = 0;

MU_TEST(test_dummy) {
    mu_assert("1 should be equal to 1", 1 == 1);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_dummy);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
EOF
    echo "✔ File test/test_dummy.c created."
else
    echo "✔ File test/test_dummy.c already exists."
fi

# Recommendation for Makefile integration if either was created
if [ ! -f "$BASE_DIR/$INCLUDE_DIR/minunit.h" ] || [ ! -d "$BASE_DIR/test" ]; then
    echo -e "\nIf you want to integrate MinUnit with your Makefile, add the following target (simple):\n"
    echo -e 'minunit:\n\tcc -I$INCLUDE_DIR test/test_dummy.c -o test_dummy\n\t./test_dummy'
    echo -e "\nFor more complex projects (with dependencies and linking), use:\n"
    echo -e 'TEST_NAME = test_binary\nTEST_SRC = test/test_suite.c\nTEST_OBJS = $(TEST_SRC:.c=.o)\n\n$(TEST_NAME): $(TEST_OBJS) src_module.o $INCLUDE_DIR/minunit.h\n\tcc -I$INCLUDE_DIR $(TEST_OBJS) src_module.o -o $(TEST_NAME) -lpthread\n\ntest: $(TEST_NAME)\n\t./$(TEST_NAME)'
fi

# Final message
echo -e "\nMinUnit setup complete! Structure ready to use."
