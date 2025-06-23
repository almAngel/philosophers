#!/bin/bash
# functional_tests/test_deadlock.sh: Comprueba que no hay deadlock y todos los filósofos comen al menos una vez

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="5 800 200 200 3"
OUT=functional_tests/output_deadlock.txt

$BIN $ARGS > $OUT &
PID=$!
TIMEOUT=12
sleep $TIMEOUT
kill $PID 2>/dev/null
wait $PID 2>/dev/null

for i in $(seq 1 5); do
    if ! grep -q "$i is eating" $OUT; then
        echo -e "\033[0;31mFAIL: El filósofo $i no ha comido (posible deadlock)\033[0m"
        exit 1
    fi
done

echo -e "\033[0;32mPASS: Todos los filósofos han comido al menos una vez (sin deadlock)\033[0m"
exit 0
