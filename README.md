# Producer-Consumer Problem

This project implements the classic Producer-Consumer synchronization problem using shared memory, semaphores, and threads in C. The producer generates items and places them on a shared table, while the consumer picks them up. The table can only hold two items at a time, requiring synchronization.

## To run the producer and consumer:

```./producer & ./consumer &```

The producer generates a fixed set of items and places them on the shared table. The consumer picks up and consumes these items.

Testing

The project includes several test scripts located in the tests/ folder:

```repeatTest.sh``` – Runs the producer and consumer multiple times and checks against expected output.

```stressTest.sh``` – Tests the program under a high load.

```testMultipleThreads.sh``` – Tests the program with multiple producer and consumer threads.

To execute tests, use:

```./tests/repeatTest.sh <num_threads>
./tests/stressTest.sh
./tests/testMultipleThreads.sh```

Expected Output

A successful run should produce logs similar to:

Table slot 1 empty. Produce 0xdead
Table slot 2 empty. Produce 0xbeef
Table slot 1 full.  Consume 0xdead
Table slot 1 empty. Produce 0xb0ba
Table slot 1 full.  Consume 0xb0ba
...
Table slot 1 empty. Produce 0xcab
Table slot 1 full.  Consume 0xcab
Table slot 2 full.  Consume 0xbeef

Cleanup

To remove compiled binaries and logs, use:

make clean

## Contributors
Isha Gupta
