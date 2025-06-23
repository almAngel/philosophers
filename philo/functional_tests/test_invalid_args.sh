#!/bin/bash
# functional_tests/test_invalid_args.sh: Comprueba que el programa rechaza argumentos inválidos

cd "$(dirname "$0")/.."
BIN=./philo

invalid_args=(
    ""
    "0 800 200 200"
    "-5 800 200 200"
    "5 -800 200 200"
    "5 800 -200 200"
    "5 800 200 -200"
    "5 800 200"
    "5 800 200 200 1 2"
    "abc 800 200 200"
)

for args in "${invalid_args[@]}"; do
    $BIN $args > /dev/null 2>&1 && {
        echo -e "\033[0;31mFAIL: El programa aceptó argumentos inválidos: '$args'\033[0m"
        exit 1
    }
done

echo -e "\033[0;32mPASS: El programa rechaza correctamente todos los argumentos inválidos\033[0m"
exit 0
