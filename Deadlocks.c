#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_function(void *arg) {
    pthread_mutex_lock(&lock1);
    printf("Thread 1: segurou o lock1\n");

    // Simulando um delay
    sleep(1);

    pthread_mutex_lock(&lock2);
    printf("Thread 1: segurou o lock2\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void *thread2_function(void *arg) {
    pthread_mutex_lock(&lock2);
    printf("Thread 2: segurou o lock2\n");

    // Simulando um delay
    sleep(1);

    pthread_mutex_lock(&lock1);
    printf("Thread 2: segurou o lock1\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Criando as threads
    pthread_create(&t1, NULL, thread1_function, NULL);
    pthread_create(&t2, NULL, thread2_function, NULL);

    // Esperando as threads terminarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}
