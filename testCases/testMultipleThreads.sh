#!/bin/bash
for threads in 1 2 4; do
    echo "Testing with $threads threads..."
    ./repeatedTest.sh 0.01 "$threads" || exit 1
done
echo "All thread configurations passed."
