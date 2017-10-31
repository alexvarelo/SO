
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_BUFFER        3096     /* tamanio del buffer */
#define DATOS_A_PRODUCIR   40000  /* datos a producir */

/* Codigo incorrecto!!! */

/* Cada Consumidor manda a consumir sus DATOS_A_PRODUCIR
  Cada productor manda a producir sus DATOS_A_PRODUCIR */

/*Al hacerlo con un while no perdemos datos*/

void *Productor(void *arg);
void *Consumidor(void *arg);

int n_elementos;           /*numero de elementos en el buffer*/
int pos_p = 0;
int pos_c = 0;
int buffer[MAX_BUFFER];    /*buffer comun*/

void main(int argc, char *argv[]){
    pthread_t th1, th2, th3, th4, th5, th6;

    pthread_create(&th1, NULL, Consumidor, NULL);
    pthread_create(&th2, NULL, Productor, NULL);
    pthread_create(&th3, NULL, Productor, NULL);
    pthread_create(&th4, NULL, Consumidor, NULL);
    pthread_create(&th5, NULL, Consumidor, NULL);
    pthread_create(&th6, NULL, Productor, NULL);
    pthread_exit(NULL);
    exit(0);
}
void *Productor(void *arg)
{
   /* codigo del productor */
	int i=0;
	int dato = 0;

  while (i < DATOS_A_PRODUCIR) {
    pthread_mutex_lock(&cerrojoComun);
        if (n_elementos < MAX_BUFFER)
	      {
          pthread_mutex_unlock(&cerrojoComun);
     		    dato=dato+1;
             /*Compartir dato*/
            pthread_mutex_lock(&cerrojoProd);
            buffer[pos_p] = dato;
		        printf("Produce %d \n", dato);
		        fflush(stdout);
            pos_p = (pos_p + 1) % MAX_BUFFER;
            pthread_mutex_unlock(&cerrojoProd);
            pthread_mutex_lock(&cerrojoComun);
            n_elementos ++;
            pthread_mutex_unlock(&cerrojoComun);
            i++;
          }
          else pthread_mutex_unlock(&cerrojoComun);
    }
    pthread_exit(0);
}

void *Consumidor(void *arg) {   /* codigo del consumidor */
  int i=0;
	int dato = 0;

  while (i < DATOS_A_PRODUCIR) {

	   if (n_elementos > 0)
	    {
	           /*Retirar dato del buffer*/
            dato = buffer[pos_c];
            pos_c = (pos_c + 1) % MAX_BUFFER;
            printf("Consume %d \n", dato);     /* consume dato */
	          fflush(stdout);
            n_elementos --;
            i++;
       }
   }
   pthread_exit(0);
}
