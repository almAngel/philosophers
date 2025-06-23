#!/bin/bash
# functional_tests/test_many_philos.sh: Comprueba robustez con muchos filósofos

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="50 800 200 200 2"
OUT=functional_tests/output_many_philos.txt

$BIN $ARGS > $OUT &
PID=$!
TIMEOUT=20
sleep $TIMEOUT
kill $PID 2>/dev/null
wait $PID 2>/dev/null

for i in $(seq 1 50); do
    count=$(grep -c "$i is eating" $OUT)
    if [ "$count" -lt 2 ]; then
        echo -e "\033[0;31mFAIL: El filósofo $i no ha comido 2 veces (posible starvation/crash)\033[0m"
        exit 1
    fi
done

echo -e "\033[0;32mPASS: Todos los filósofos han comido al menos 2 veces (robustez OK)\033[0m"
exit 0
