#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX_BUFFER         1024      /* tamanio del buffer */
#define DATOS_A_PRODUCIR   100000    /* datos a producir */

/*Este código funciona perfectamente independientemente del número de hilos
tanto de productor como de consumidor que se tengan, utilizamos el cerroojo
para proteger TODO el proceso de lectura-escritura sobre el buffer*/


pthread_mutex_t mutex;     /*mutex para buffer compartido*/
pthread_cond_t lleno;      /*controla el llenado del buffer*/
pthread_cond_t vacio;      /*controla el vaciado del buffer*/

int n_elementos;           /*numero de elementos en el buffer*/
int pos_p = 0;            /*Puntero buffer para producir*/
int pos_c = 0;            /*Puntero buffer para comsumir*/
int buffer[MAX_BUFFER];    /*buffer comun*/

void *Productor(void *arg);
void *Consumidor(void *arg);

int main(int argc, char *argv[]){
    pthread_t th1, th2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&lleno, NULL);
    pthread_cond_init(&vacio, NULL);
    pthread_create(&th1, NULL, Productor, NULL);
    pthread_create(&th2, NULL, Consumidor, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&lleno);
    pthread_cond_destroy(&vacio);
    exit(0);
}
void *Productor(void *arg)
{
   /* codigo del productor */
    int dato, i ,pos = 0;

    for(i=0; i < DATOS_A_PRODUCIR; i++ )  {
        dato = dato+5;           /*producir dato*/
        pthread_mutex_lock(&mutex);       /*acceder al buffer*/
        if (n_elementos == MAX_BUFFER) /*si buffer lleno*/
            pthread_cond_wait(&lleno, &mutex); /*se bloquea*/
        /*Compartir dato*/
        buffer[pos_p] = dato;
	printf("%d %d\n", pos, dato);
        pos_p = (pos_p + 1) % MAX_BUFFER;
        n_elementos ++;
	      pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&vacio);   /*buffer no vacio*/
    }
    pthread_exit(0);
}

void *Consumidor(void *arg) {   /* codigo del consumidor */
    int dato, i ,pos = 0;

    for(i=0; i < DATOS_A_PRODUCIR; i++ ) {
        pthread_mutex_lock(&mutex);    /* acceder al buffer */
        if (n_elementos == 0)       /* si buffer vacio */
            pthread_cond_wait(&vacio, &mutex); /* se bloquea */
        /*Retirar dato del buffer*/
        dato = buffer[pos_c];
        pos_c = (pos_c + 1) % MAX_BUFFER;
        printf("%d\n", dato);
        n_elementos --;
        pthread_mutex_unlock(&mutex);
	   pthread_cond_signal(&lleno);   /* buffer no lleno */
    }
    pthread_exit(0);
}
