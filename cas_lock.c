#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

#define THREADS 5

atomic_int lock = 0;

void acquire_lock() {
    int expected;
    do {
        expected = 0;
    } while (!atomic_compare_exchange_strong(&lock, &expected, 1));
}

void release_lock() {
    atomic_store(&lock, 0);
}

void* critical_section(void* arg) {
    int id = *(int*)arg;

    acquire_lock();
    printf("Thread %d entered critical section\n", id);

    // Simulate work
    for (volatile int i = 0; i < 100000000; i++);

    printf("Thread %d leaving critical section\n", id);
    release_lock();

    return NULL;
}

int main() {
    pthread_t t[THREADS];
    int id[THREADS];

    for (int i = 0; i < THREADS; i++) {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, critical_section, &id[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    return 0;
}