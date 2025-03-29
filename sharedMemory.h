//Isha Gupta
//3.28.2025
#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

// Modifiable constants
const char *sharedMemoryName = "/producerConsumerTable";
const unsigned int nItemSlots = 2; // Buffer size
const float defaultDelay = 0.01;

// Shared Memory Structure
struct sharedMemory {
    sem_t *mutex;
    sem_t *emptySlots;
    sem_t *fullSlots;
    unsigned short *items;
};

// Global delay variable
float delay;

// Initialize Shared Memory & Semaphores
struct sharedMemory initializeSharedMemory(const char *name) {
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); exit(1); }
    size_t tableSize = sizeof(sem_t) * 3 + sizeof(unsigned short) * nItemSlots;
    ftruncate(fd, tableSize);

    void *ptr = mmap(NULL, tableSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); exit(3); }

    struct sharedMemory shm;
    shm.mutex = (sem_t*) ptr;
    shm.emptySlots = (sem_t*)((char*)ptr + sizeof(sem_t));
    shm.fullSlots = (sem_t*)((char*)ptr + 2 * sizeof(sem_t));
    shm.items = (unsigned short*)((char*)ptr + 3 * sizeof(sem_t));

    sem_init(shm.mutex, 1, 1);
    sem_init(shm.emptySlots, 1, nItemSlots);
    sem_init(shm.fullSlots, 1, 0);

    return shm;
}

// Run Producer or Consumer
int run(int argc, char *argv[], void* (*produceOrConsumeItems)(void*)) {
    setbuf(stdout, NULL);
    struct sharedMemory shm = initializeSharedMemory(sharedMemoryName);
    
    delay = (argc > 1) ? atof(argv[1]) : defaultDelay;
    unsigned int num_threads = (argc > 2) ? atoi(argv[2]) : 1;

    pthread_t threads[num_threads];
    for (unsigned int i = 0; i < num_threads; ++i)
        pthread_create(&threads[i], NULL, produceOrConsumeItems, (void *) &shm);

    for (unsigned int i = 0; i < num_threads; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}

#endif
