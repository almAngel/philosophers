#!/bin/bash
# functional_tests/test_starvation.sh: Comprueba que no hay starvation (todos comen varias veces)

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="5 800 200 200 5"
OUT=functional_tests/output_starvation.txt

$BIN $ARGS > $OUT &
PID=$!
TIMEOUT=15
sleep $TIMEOUT
kill $PID 2>/dev/null
wait $PID 2>/dev/null

for i in $(seq 1 5); do
    count=$(grep -c "$i is eating" $OUT)
    if [ "$count" -lt 5 ]; then
        echo -e "\033[0;31mFAIL: El filósofo $i ha comido solo $count veces (posible starvation)\033[0m"
        exit 1
    fi
done

echo -e "\033[0;32mPASS: Todos los filósofos han comido al menos 5 veces (sin starvation)\033[0m"
exit 0
