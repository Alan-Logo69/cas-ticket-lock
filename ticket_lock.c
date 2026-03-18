#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

#define THREADS 5

atomic_int next_ticket = 0;
atomic_int now_serving = 0;

void acquire_lock(int* my_ticket) {
    *my_ticket = atomic_fetch_add(&next_ticket, 1);

    while (atomic_load(&now_serving) != *my_ticket);
}

void release_lock() {
    atomic_fetch_add(&now_serving, 1);
}

void* critical_section(void* arg) {
    int id = *(int*)arg;
    int my_ticket;

    acquire_lock(&my_ticket);

    printf("Thread %d (Ticket %d) entered CS\n", id, my_ticket);

    for (volatile int i = 0; i < 100000000; i++);

    printf("Thread %d leaving CS\n", id);

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