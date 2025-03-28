#include "sharedMemory.h"

#define nItems 14
const unsigned short int items[nItems] = {
    0xDEAD, 0xBEEF, 0xB0BA, 0xBABE, 0x0BAD, 0xCAFE, 0xF00D,
    0x0BEE, 0x0F00, 0x0DAD, 0xC0DE, 0xFACE, 0xB00B, 0x0CAB
};

void *produceItems(void *args) {
    struct sharedMemory *shm = (struct sharedMemory *) args;
    unsigned int item = 0;

    while (item < nItems) {
        sem_wait(shm->emptySlots); // Wait if buffer is full
        sem_wait(shm->mutex);

        for (unsigned int slot = 0; slot < nItemSlots; ++slot) {
            if (shm->items[slot] == 0) {
                printf("Producer: Table slot %d empty. Producing 0x%x\n", slot + 1, items[item]);
                shm->items[slot] = items[item++];
                break;
            }
        }

        sem_post(shm->mutex);
        sem_post(shm->fullSlots); // Signal consumer

        usleep((useconds_t)(delay * 1e6));
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    run(argc, argv, &produceItems);
}
