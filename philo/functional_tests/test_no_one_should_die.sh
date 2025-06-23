#!/bin/bash
# functional_tests/test_no_one_should_die.sh: Test funcional para comprobar que nadie muere y la simulación no termina antes de tiempo

cd "$(dirname "$0")/.."
BIN=./philo
ARGS="5 800 200 200"
OUT=functional_tests/output_no_one_should_die.txt

# Lanza el programa en segundo plano
$BIN $ARGS > $OUT &
PID=$!

# Espera 10 segundos
sleep 10

# Comprueba si el proceso sigue vivo
if ! kill -0 $PID 2>/dev/null; then
    echo -e "\033[0;31mFAIL: El programa terminó prematuramente\033[0m"
    cat $OUT
    exit 1
fi

# Mata el proceso
kill $PID
wait $PID 2>/dev/null

# Comprueba que no haya mensaje de muerte
if grep -q "died" $OUT; then
    echo -e "\033[0;31mFAIL: Algún filósofo murió\033[0m"
    cat $OUT
    exit 1
fi

echo -e "\033[0;32mPASS: Nadie murió y la simulación no terminó antes de tiempo\033[0m"
exit 0
