CC = gcc
CFLAGS = -pthread -lrt -Wall -Wextra

# Source files
SRC_PRODUCER = producer.c
SRC_CONSUMER = consumer.c
SRC_SHARED = sharedMemory.h

# Output executables
OUT_PRODUCER = producer
OUT_CONSUMER = consumer

# Test files directory
TEST_DIR = tests

# Default rule
all: $(OUT_PRODUCER) $(OUT_CONSUMER)

# Compile producer
$(OUT_PRODUCER): $(SRC_PRODUCER) $(SRC_SHARED)
	$(CC) $(CFLAGS) $(SRC_PRODUCER) -o $(OUT_PRODUCER)

# Compile consumer
$(OUT_CONSUMER): $(SRC_CONSUMER) $(SRC_SHARED)
	$(CC) $(CFLAGS) $(SRC_CONSUMER) -o $(OUT_CONSUMER)

# Run tests
.PHONY: test

test: all
	@echo "Running tests..."
	@bash $(TEST_DIR)/repeatTest.sh 0.01 1
	@bash $(TEST_DIR)/stressTest.sh 0.01 2
	@bash $(TEST_DIR)/testMultipleThreads.sh 0.01 3
	@echo "All tests completed."

# Clean build artifacts
.PHONY: clean

clean:
	rm -f $(OUT_PRODUCER) $(OUT_CONSUMER) log.txt
	rm -f $(TEST_DIR)/logTable.txt
