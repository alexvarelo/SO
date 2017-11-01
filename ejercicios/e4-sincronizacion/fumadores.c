#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t cerrojo;     /*mutex para buffer compartido*/
pthread_cond_t llena;      /*controla el llenado del buffer*/
pthread_cond_t vacia;      /*controla el vaciado del buffer*/

int mesa=0;

void *Agente(void *arg);
void *Fumador(void *arg);

int main(int argc, char *argv[]){
    pthread_t f1, f2, f3, a1;
    pthread_mutex_init(&cerrojo, NULL);
    pthread_cond_init(&llena, NULL);
    pthread_cond_init(&vacia, NULL);
    int i1 = 1, i2 = 2, i3 = 3;
    pthread_create(&f1, NULL, Fumador, &i1);
    pthread_create(&f2, NULL, Fumador, &i2);
    pthread_create(&f3, NULL, Fumador, &i3);
    pthread_create(&a1, NULL, Agente, NULL);
    pthread_join(f1, NULL);
    pthread_join(f2, NULL);
    pthread_join(a1, NULL);
    pthread_mutex_destroy(&cerrojo);
    pthread_cond_destroy(&llena);
    pthread_cond_destroy(&vacia);
    exit(0);
}
int generaIngrediente(){
    return rand()%3+1;
}

void *Agente(void *arg){
    int i1, i2;
    while(1){
    i1=generaIngrediente();
    i2=generaIngrediente();
    while(i1==i2)
        i2=generaIngrediente();
    
    printf("Agente: quiero dejar %d %d en la mesa.\n", i1, i2);
    pthread_mutex_lock(&cerrojo);
    if (mesa != 0)
        pthread_cond_wait(&llena, &cerrojo);
    mesa=i1+i2;
    printf("Agente: pongo %d %d en la mesa.\n", i1, i2);
    
    pthread_mutex_unlock(&cerrojo);
   // pthread_cond_signal(&vacia);
}
    pthread_exit(0);  
}

void *Fumador(void *arg) { 
    int *miIngrediente = (int *)arg;
    while(1){
    pthread_mutex_lock(&cerrojo); 
    if(mesa+(*miIngrediente) == 6){
     //   pthread_cond_wait(&vacia, &cerrojo);
    printf("Fumador: tengo %d y cojo los %d que necesito para tener %d.\n", (*miIngrediente), mesa, mesa+(*miIngrediente));
    mesa = 0;
    }
    pthread_mutex_unlock(&cerrojo);
    pthread_cond_signal(&llena);
    
}
    pthread_exit(0);
}    