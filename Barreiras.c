#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
pthread_barrier_t barrier;

void *thread_function(void *arg) {
    int id = *((int *)arg);
    printf("Thread %d chegando na barreira\n", id);
    pthread_barrier_wait(&barrier);  // Sincronizando todas as threads

    // Todas as threads chegam na barreira antes de continuar
    printf("Thread %d passou pela barreira\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicializando a barreira
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Criando as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Esperando as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruindo a barreira
    pthread_barrier_destroy(&barrier);
    return 0;
}
