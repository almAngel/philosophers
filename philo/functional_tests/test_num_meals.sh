#!/bin/bash
# functional_tests/test_num_meals.sh: Comprueba que el programa termina cuando todos han comido el número requerido de veces

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="3 800 200 200 3"
OUT=functional_tests/output_num_meals.txt

$BIN $ARGS > $OUT &
PID=$!
TIMEOUT=10
sleep $TIMEOUT
if kill -0 $PID 2>/dev/null; then
    echo "FAIL: El programa no terminó tras alcanzar el número de comidas"
    kill $PID
    wait $PID 2>/dev/null
    exit 1
fi

for i in $(seq 1 3); do
    count=$(grep -c "$i is eating" $OUT)
    if [ "$count" -lt 3 ]; then
        echo -e "\033[0;31mFAIL: El filósofo $i no ha comido 3 veces\033[0m"
        exit 1
    fi
done

echo -e "\033[0;32mPASS: Todos los filósofos han comido 3 veces y el programa terminó correctamente\033[0m"
exit 0
