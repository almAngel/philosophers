#!/bin/bash
# functional_tests/test_fork_logic.sh: Comprueba que los filósofos no toman dos forks seguidos sin alternancia

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="2 800 200 200 1"
OUT=functional_tests/output_fork_logic.txt

$BIN $ARGS > $OUT

# Busca líneas donde el mismo filósofo toma dos forks seguidos
grep_fail=0
awk '/has taken a fork/ { \
    if (last_philo == $2 && last_time == $1) { print "FAIL: Filósofo " $2 " toma dos forks seguidos en el mismo instante"; exit 1 }
    last_philo = $2; last_time = $1
}' $OUT || grep_fail=1

# Busca si ambos filósofos comen a la vez (no debería pasar)
if grep -q '1 is eating' $OUT && grep -q '2 is eating' $OUT; then
    if grep -E '1 is eating.*2 is eating|2 is eating.*1 is eating' $OUT; then
        echo -e "\033[0;31mFAIL: Ambos filósofos comen a la vez\033[0m"
        exit 1
    fi
fi

if [ $grep_fail -eq 1 ]; then
    exit 1
fi

echo -e "\033[0;32mPASS: La lógica de forks parece correcta (no hay doble toma ni doble comida simultánea)\033[0m"
exit 0
