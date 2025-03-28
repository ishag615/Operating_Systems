#!/bin/bash
echo "Running stress test..."
for delay in 0.01 0.005 0.001; do
    for threads in 1 2 4; do
        echo "Testing with delay $delay and $threads threads..."
        ./repeatedTest.sh "$delay" "$threads" || exit 1
    done
done
echo "Stress test passed!"
