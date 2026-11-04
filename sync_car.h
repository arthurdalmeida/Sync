#ifndef SYNC_CAR_H
#define SYNC_CAR_H
#include <pthread.h>

typedef struct station{
    pthread_mutex_t mutex;
    pthread_cond_t carroChegou;
    pthread_cond_t todosSentados;
    int esperando;
    int assentosLivres;
    int passageirosACaminho;
} station;

void station_init(struct station *station);
void station_load_car(struct station *station, int cont);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);

#endif