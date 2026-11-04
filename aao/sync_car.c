#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sync_car.h"


void station_init(struct station *station){
    station->esperando = 0;
    station->assentosLivres = 0;
    station->passageirosACaminho = 0;

    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->carroChegou, NULL);
    pthread_cond_init(&station->todosSentados, NULL);
}

void station_wait_for_car(struct station *station){
    pthread_mutex_lock(&station->mutex);

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

    while (station->passageirosACaminho > 0){
        pthread_cond_wait(&station->todosSentados, &station->mutex);
    }

    pthread_cond_signal(&station->todosSentados);

    pthread_mutex_unlock(&station->mutex);
}

void station_load_car(struct station *station, int cont){
    pthread_mutex_lock(&station->mutex);

    station->assentosLivres = cont;

    pthread_cond_broadcast(&station->carroChegou);

    pthread_cond_wait(&station->todosSentados, &station->mutex);

    station->assentosLivres = 0;

    pthread_mutex_unlock(&station->mutex);
}