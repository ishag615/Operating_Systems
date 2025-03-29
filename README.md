# Producer-Consumer Problem

This project implements the classic Producer-Consumer synchronization problem using shared memory, semaphores, and threads in C. The producer generates items and places them on a shared table, while the consumer picks them up. The table can only hold two items at a time, requiring synchronization.

## To run the producer and consumer:

```./producer & ./consumer &```

The producer generates a fixed set of items and places them on the shared table. The consumer picks up and consumes these items.

## Testing

The project includes several test scripts located in the tests/ folder:

repeatTest.sh – Runs the producer and consumer multiple times and checks against expected output.

stressTest.sh – Tests the program under a high load.

testMultipleThreads.sh – Tests the program with multiple producer and consumer threads.

To execute tests, use:

```./tests/repeatTest.sh <num_threads>```
```./tests/stressTest.sh```
```./tests/testMultipleThreads.sh ```

## Expected Output

A successful run should produce logs similar to:

Table slot 1 empty. Produce 0xdead
Table slot 2 empty. Produce 0xhell
Table slot 1 full.  Consume 0xisha
Table slot 1 empty. Produce 0xmama
Table slot 1 full.  Consume 0xb0ba
Table slot 1 empty. Produce 0xbaby
Table slot 1 full.  Consume 0xbabe
...
Table slot 1 full.  Consume 0xfunc
Table slot 1 empty. Produce 0xmama
Table slot 1 full.  Consume 0xdad
Table slot 1 empty. Produce 0xc0de
Table slot 1 full.  Consume 0xc0de
Table slot 1 empty. Produce 0xface
Table slot 1 full.  Consume 0xtail
Table slot 1 empty. Produce 0xred
Table slot 1 full.  Consume 0xhead
Table slot 1 empty. Produce 0xcab0
Table slot 1 full.  Consume 0xduzz
Table slot 2 full.  Consume 0xdiya


## Cleanup

To remove compiled binaries and logs, use:

```make clean```

## Contributors
Isha Gupta
