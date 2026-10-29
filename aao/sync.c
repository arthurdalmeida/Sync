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

void station_init(struct station *station){
    station->esperando = 0;
    station->assentosLivres = 0;
    station->passageirosACaminho = 0;

    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->carroChegou, NULL);
    pthread_cond_init(&station->todosSentados, NULL);
}