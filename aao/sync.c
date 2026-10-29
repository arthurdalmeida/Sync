#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct station{
    pthread_mutex_t mutex;
    pthread_cond_t carroChegou;
    pthread_cond_t todosSentados;
    int esperando;
    int assentosLivres;
    int passageirosACaminho;
} station;