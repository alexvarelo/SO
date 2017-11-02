#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

#define MAX_RACIONES         20      /* tamanio del buffer */


/*Este código funciona perfectamente independientemente del número de hilos

tanto de productor como de consumidor que se tengan, utilizamos el cerroojo

para proteger TODO el proceso de lectura-escritura sobre el buffer*/



pthread_mutex_t mutex;     /*mutex para buffer compartido*/

pthread_cond_t vacio;      /*controla el vaciado del buffer*/

pthread_cond_t lleno;      /*controla el llenado del buffer*/


int raciones = 0;           /*numero de elementos en el buffer*/


void *Cocinero(void *arg);

void *Salvaje(void *arg);


int main(int argc, char *argv[]){

    pthread_t th1, th2, th3, th4, th5;

    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&vacio, NULL);

    pthread_cond_init(&lleno, NULL);

    pthread_create(&th1, NULL, Cocinero, NULL);

    pthread_create(&th2, NULL, Salvaje, NULL);

    pthread_create(&th3, NULL, Salvaje, NULL);

    pthread_create(&th4, NULL, Salvaje, NULL);

    pthread_create(&th5, NULL, Salvaje, NULL);

    pthread_join(th1, NULL);

    pthread_join(th2, NULL);

    pthread_join(th3, NULL);

    pthread_join(th4, NULL);

    pthread_join(th5, NULL);

    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&vacio);

    pthread_cond_destroy(&lleno);

    exit(0);

}

void getServingFromPot(){

    raciones--;

    printf("Racion consumida, quedan %d\n", raciones);

}


void putServingsInPot(int m){

    raciones = m;

    printf("El cocinero ha rellenado caldero con %d raciones\n", raciones);

}


void *Cocinero(void *arg)

{

   /* codigo del productor */

    while(1)  {

        pthread_mutex_lock(&mutex);       

        /*Compartir dato*/

        if(raciones == 0){

            putServingsInPot(MAX_RACIONES);

            pthread_cond_signal(&vacio);   /*buffer no vacio*/

        }

        else{

            pthread_cond_wait(&lleno, &mutex);

        }

   pthread_mutex_unlock(&mutex);

    }

    pthread_exit(0);

}


void *Salvaje(void *arg) {   /* codigo del consumidor */

    while(1) {

        pthread_mutex_lock(&mutex);    /* acceder al buffer */

        if (raciones == 0){       /* si buffer vacio */

            pthread_cond_signal(&lleno);

            pthread_cond_wait(&vacio, &mutex); /* se bloquea */

    }

        /*Servir racion*/

        getServingFromPot();

        pthread_mutex_unlock(&mutex);

        //sleep(1); //Activar para ver el desarrollo mejor

    }

    pthread_exit(0);

}
