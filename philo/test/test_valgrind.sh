#!/bin/bash
# Test script for memory testing with strict valgrind

cd "$(dirname "$0")/.."
BIN=./philo

echo "=== VALGRIND MEMORY TESTS ==="
echo

# Test 1: Basic memory leak test
echo "Test 1: Basic memory leak test (4 philosophers, 3 meals)"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
    $BIN 4 800 200 200 3 2>/tmp/valgrind_basic.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No memory leaks detected"
else
    echo "❌ FAIL: Memory issues detected"
    echo "--- Valgrind output ---"
    cat /tmp/valgrind_basic.log
fi
echo

# Test 2: Race condition detection with helgrind
echo "Test 2: Race condition detection (5 philosophers)"
valgrind --tool=helgrind --error-exitcode=1 \
    $BIN 5 800 200 200 2 2>/tmp/valgrind_helgrind.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No race conditions detected"
else
    echo "❌ FAIL: Race conditions detected"
    echo "--- Helgrind output ---"
    cat /tmp/valgrind_helgrind.log
fi
echo

# Test 3: Thread error detection with DRD
echo "Test 3: Thread error detection with DRD (3 philosophers)"
valgrind --tool=drd --error-exitcode=1 \
    $BIN 3 800 200 200 2 2>/tmp/valgrind_drd.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No thread errors detected"
else
    echo "❌ FAIL: Thread errors detected"
    echo "--- DRD output ---"
    cat /tmp/valgrind_drd.log
fi
echo

# Test 4: Memory leak with many philosophers
echo "Test 4: Memory leak test with many philosophers (10 philosophers, 2 meals)"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
    $BIN 10 800 200 200 2 2>/tmp/valgrind_many.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No memory leaks with many philosophers"
else
    echo "❌ FAIL: Memory issues with many philosophers"
    echo "--- Valgrind output ---"
    cat /tmp/valgrind_many.log
fi
echo

# Test 5: Single philosopher edge case
echo "Test 5: Single philosopher memory test"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
    $BIN 1 800 200 200 1 2>/tmp/valgrind_single.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No memory leaks with single philosopher"
else
    echo "❌ FAIL: Memory issues with single philosopher"
    echo "--- Valgrind output ---"
    cat /tmp/valgrind_single.log
fi
echo

# Test 6: Stress test with valgrind (shorter duration)
echo "Test 6: Stress test memory check (20 philosophers, 1 meal)"
timeout 10s valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 \
    $BIN 20 600 200 200 1 2>/tmp/valgrind_stress.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No memory leaks in stress test"
else
    echo "❌ FAIL: Memory issues in stress test"
    echo "--- Valgrind output ---"
    cat /tmp/valgrind_stress.log
fi
echo

# Test 7: Check for uninitialized memory reads
echo "Test 7: Uninitialized memory detection"
valgrind --memcheck:track-origins=yes --error-exitcode=1 \
    $BIN 4 800 200 200 2 2>/tmp/valgrind_uninit.log
if [ $? -eq 0 ]; then
    echo "✅ PASS: No uninitialized memory usage"
else
    echo "❌ FAIL: Uninitialized memory detected"
    echo "--- Valgrind output ---"
    cat /tmp/valgrind_uninit.log
fi
echo

echo "=== VALGRIND TESTS COMPLETE ==="
echo "Check individual log files in /tmp/valgrind_*.log for detailed output"

# Cleanup
# rm -f /tmp/valgrind_*.log
