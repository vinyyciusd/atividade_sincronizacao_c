#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_ITEMS 5
int buffer = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_produtor = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumidor = PTHREAD_COND_INITIALIZER;

void *produtor(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer > 0) {  // Espera até o buffer ser consumido
            pthread_cond_wait(&cond_produtor, &mutex);
        }
        buffer++;  // Produz um item
        printf("Produtor produziu: %d\n", buffer);
        pthread_cond_signal(&cond_consumidor);  // Sinaliza o consumidor
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumidor(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer == 0) {  // Espera até o buffer ter algo para consumir
            pthread_cond_wait(&cond_consumidor, &mutex);
        }
        printf("Consumidor consumiu: %d\n", buffer);
        buffer--;  // Consome o item
        pthread_cond_signal(&cond_produtor);  // Sinaliza o produtor
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t_produtor, t_consumidor;

    // Criando as threads
    pthread_create(&t_produtor, NULL, produtor, NULL);
    pthread_create(&t_consumidor, NULL, consumidor, NULL);

    // Esperando as threads terminarem
    pthread_join(t_produtor, NULL);
    pthread_join(t_consumidor, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_produtor);
    pthread_cond_destroy(&cond_consumidor);
    return 0;
}
