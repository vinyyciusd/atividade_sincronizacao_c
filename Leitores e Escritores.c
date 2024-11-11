#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void *arg) {
    pthread_rwlock_rdlock(&rwlock);  // Leitor adquire o bloqueio de leitura
    printf("Leitor lendo...\n");
    pthread_rwlock_unlock(&rwlock);  // Leitor libera o bloqueio de leitura
    return NULL;
}

void *writer(void *arg) {
    pthread_rwlock_wrlock(&rwlock);  // Escritor adquire o bloqueio de escrita
    printf("Escritor escrevendo...\n");
    pthread_rwlock_unlock(&rwlock);  // Escritor libera o bloqueio de escrita
    return NULL;
}

int main() {
    pthread_t threads[5];
    
    // Criando threads de leitores e escritores
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, reader, NULL);
    }
    for (int i = 3; i < 5; i++) {
        pthread_create(&threads[i], NULL, writer, NULL);
    }

    // Esperando as threads terminarem
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
