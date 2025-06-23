#!/bin/bash
# minunit-purge.sh
# Script to completely remove MinUnit setup from any C project
# Author: Angello López Molina

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <include_dir>"
    echo "Example: $0 includes"
    exit 1
fi
INCLUDE_DIR="$1"

BASE_DIR=$(pwd)

# Prompt before removing minunit.h
if [ -f "$BASE_DIR/$INCLUDE_DIR/minunit.h" ]; then
    read -p "Are you sure you want to remove $INCLUDE_DIR/minunit.h? [y/n]: " CONFIRM_MINUNIT
    if [[ "$CONFIRM_MINUNIT" =~ ^[Yy]$ ]]; then
        rm "$BASE_DIR/$INCLUDE_DIR/minunit.h"
        echo "✔ Removed $INCLUDE_DIR/minunit.h"
    else
        echo "Skipped removing $INCLUDE_DIR/minunit.h."
    fi
else
    echo "No minunit.h found in $INCLUDE_DIR."
fi

# Prompt before removing test_dummy.c
if [ -f "$BASE_DIR/test/test_dummy.c" ]; then
    read -p "Are you sure you want to remove test/test_dummy.c? [y/n]: " CONFIRM_DUMMY
    if [[ "$CONFIRM_DUMMY" =~ ^[Yy]$ ]]; then
        rm "$BASE_DIR/test/test_dummy.c"
        echo "✔ Removed test/test_dummy.c"
    else
        echo "Skipped removing test/test_dummy.c."
    fi
else
    echo "No test_dummy.c found in test/."
fi

# Prompt before removing test/ directory if empty
if [ -d "$BASE_DIR/test" ] && [ ! "$(ls -A $BASE_DIR/test)" ]; then
    read -p "test/ directory is empty. Do you want to remove it? [y/n]: " CONFIRM_TESTDIR
    if [[ "$CONFIRM_TESTDIR" =~ ^[Yy]$ ]]; then
        rmdir "$BASE_DIR/test"
        echo "✔ Removed empty test/ directory"
    else
        echo "Skipped removing test/ directory."
    fi
fi

# Advise about Makefile
echo -e "\nIf you had a MinUnit target in your Makefile, please remove it manually.\nFor example, remove lines like (simple):\n"
echo -e 'minunit:\n\tcc -I$INCLUDE_DIR test/test_dummy.c -o test_dummy\n\t./test_dummy'
echo -e "\nOr for more complex projects (with dependencies and linking):\n"
echo -e 'TEST_NAME = test_binary\nTEST_SRC = test/test_suite.c\nTEST_OBJS = $(TEST_SRC:.c=.o)\n\n$(TEST_NAME): $(TEST_OBJS) src_module.o $INCLUDE_DIR/minunit.h\n\tcc -I$INCLUDE_DIR $(TEST_OBJS) src_module.o -o $(TEST_NAME) -lpthread\n\ntest: $(TEST_NAME)\n\t./$(TEST_NAME)'

echo -e "\nMinUnit purge complete!"
