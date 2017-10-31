#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t cerrojo;     /*cerrojo para dato compartido*/
pthread_mutex_t lectores;    /*cerrojo para n_lect*/
			     /*son "variables" compartida por todos los hilos*/

int dato = 5;                   /*recurso*/
int n_lect = 0;                 /*numero de lectores (tambien es un recurso)*/

void *Lector(void *arg);
void *Escritor(void *arg);

int main(int argc, char *argv[])  {
    pthread_t th1, th2, th3, th4;
    
    /*Se inicializan cerrojos, se informa al SO*/
    pthread_mutex_init(&cerrojo, NULL);
    /*----------------------------------------*/

    pthread_create(&th1, NULL, Lector, NULL);
    pthread_create(&th2, NULL, Escritor, NULL);
    pthread_create(&th3, NULL, Lector, NULL);
    pthread_create(&th4, NULL, Escritor, NULL);

    pthread_join(th1, NULL);    pthread_join(th2, NULL);
    pthread_join(th3, NULL);    pthread_join(th4, NULL);
    
    /*Se destruyen cerrojos, se libera ese recurso*/
    pthread_mutex_destroy(&cerrojo);
    /*----------------------------------------*/

    exit(0);
}

/*codigo del lector */
void *Lector(void *arg) {
   while(1){
     
     pthread_mutex_lock(&cerrojo);
     n_lect ++;
     
     /*leer*/
     printf("%d\n", dato);
         
     n_lect--;
     pthread_mutex_unlock(&cerrojo);
     
          
  }
}

/*codigo del escritor */
void *Escritor(void *arg){
  while(1){
   
    pthread_mutex_lock(&cerrojo);
    /*modificar el recurso */
    dato = dato + 5;
    printf("modificando %d\n", dato);
    pthread_mutex_unlock(&cerrojo); 
    sleep(3);
  }
}
