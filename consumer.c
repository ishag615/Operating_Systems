#include "sharedMemory.h"

void *consumeItems(void *args) {
    struct sharedMemory *shm = (struct sharedMemory *) args;

    while (1) {
        sem_wait(shm->fullSlots); // Wait if buffer is empty
        sem_wait(shm->mutex);

        for (unsigned int slot = 0; slot < nItemSlots; ++slot) {
            if (shm->items[slot] != 0) {
                printf("Consumer: Table slot %d full. Consuming 0x%x\n", slot + 1, shm->items[slot]);
                shm->items[slot] = 0;
                break;
            }
        }

        sem_post(shm->mutex);
        sem_post(shm->emptySlots); // Signal producer

        usleep((useconds_t)(delay * 1e6));
    }
}

int main(int argc, char *argv[]) {
    run(argc, argv, &consumeItems);
}
