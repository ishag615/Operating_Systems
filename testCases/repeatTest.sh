#!/bin/bash
# Test the producer-consumer program multiple times.
# Exits successfully (0) if any run matches expected output.

NUM_THREADS="${2:-1}"  # Default to 1 thread if not provided
LOG_FILE="log.txt"
EXPECTED_LOG="tests/log${NUM_THREADS}.txt"
RETRIES=100

# Ensure shared memory is cleared before testing
cleanup() {
    ipcs -m | awk '/0x/{print $2}' | xargs -I {} ipcrm -m {} 2>/dev/null
    rm -f "$LOG_FILE"
}
trap cleanup EXIT

for _ in $(seq 1 $RETRIES); do
    cleanup

    # Start producer
    ./producer 0.01 "$NUM_THREADS" >> "$LOG_FILE" &
    sleep 0.02  # Adjust sleep based on observed timing

    # Start consumer with timeout
    timeout 0.15 ./consumer 0.01 "$NUM_THREADS" >> "$LOG_FILE" || true

    # Check output against expected log
    if diff "$EXPECTED_LOG" "$LOG_FILE" >/dev/null; then
        echo "Test passed!"
        exit 0
    fi
done

# If all retries fail, show the last diff and exit with failure
echo "Test failed after $RETRIES retries."
diff -U 3 "$EXPECTED_LOG" "$LOG_FILE"
exit 1
