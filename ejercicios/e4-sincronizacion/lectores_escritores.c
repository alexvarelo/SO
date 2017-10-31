#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int dato = 5;                   /*recurso*/
int n_lect = 0;                 

void *Lector(void *arg);
void *Escritor(void *arg);

int main(int argc, char *argv[])  {
    pthread_t th1, th2, th3, th4;
    
    pthread_create(&th1, NULL, Lector, NULL);
    pthread_create(&th2, NULL, Escritor, NULL);
    pthread_create(&th3, NULL, Lector, NULL);
    pthread_create(&th4, NULL, Escritor, NULL);

    pthread_join(th1, NULL);    pthread_join(th2, NULL);
    pthread_join(th3, NULL);    pthread_join(th4, NULL);
    
    exit(0);
}

/*codigo del lector */
void *Lector(void *arg) {
   while(1){
    pthread_mutex_lock(&lectores);
    n_lect ++;
    if(n_lect==1) pthread_mutex_lock(&cerrojo);
    pthread_mutex_unlock(&lectores);

    /*leer*/
    printf("%d\n", dato);

    pthread_mutex_lock(&lectores);
    n_lect--;
    if(n_lect==0) pthread_mutex_unlock(&cerrojo);
    pthread_mutex_unlock(&lectores);
  }
}

/*codigo del escritor */
void *Escritor(void *arg){
  while(1){
    /*modificar el recurso */
    pthread_mutex_lock(&cerrojo);
    dato = dato + 5;
    printf("modificando %d\n", dato);
    pthread_mutex_unlock(&cerrojo);
    sleep(5);
  }
}
