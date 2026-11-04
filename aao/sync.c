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

void station_wait_for_car(struct station *station){
    station->mutex = 1;

    station->esperando++;

    if (station->assentosLivres == 0){
        pthread_cond_wait(&station->carroChegou, &station->mutex);
    }

    station->esperando--;
    station->assentosLivres--;
    station->passageirosACaminho++;
}

void station_on_board(struct station *station){
    pthread_mutex_lock(&station->mutex);

    while (station->todosSentados > 0){
        pthread_cond_wait(&station->passageirosACaminho);
    }

    pthread_cond_signal(&station->todosSentados);

    pthread_mutex_unlock(&station->mutex);
}

void station_load_car(struct station *station, int cont){
    pthread_mutex_lock(&station->mutex);

    station->assentosLivres = cont;

    pthread_cond_broadcast(&station->carroChegou);

    pthread_cond_wait(&station->todosSentados);

    station->assentosLivres = 0;

    pthread_mutex_unlock(&station->mutex);
}