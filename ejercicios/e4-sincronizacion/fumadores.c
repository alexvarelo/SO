/*
E2 - Básicos sincronización
Considerar un sistema con tres procesos fumadores y un proceso agente. 
Continuamente cada fumador se prepara un cigarrillo y lo fuma. 
Para hacer un cigarrillo se necesitan tres ingredientes: tabaco, papel y cerillas.
- Uno de los procesos tiene infinito papel, otro tabaco y el tercero cerillas.
- El agente tiene provisión infinita de los tres ingredientes.
- El agente coloca dos ingredientes distintos y de forma aleatoria en la mesa.
- El fumador que tiene el ingrediente que falta puede proceder a preparar y fumar un cigarrillo, haciendo una señal al agente cuando acaba, el agente en este instante repite la operación, pone otros dos de los tres ingredientes en la mesa.
La operación se repite indefinidamente.
Escribir un programa que sincronice al agente y los fumadores mediante semáforos o mutexes y variables condicionales.
Asúmase que el agente no tiene forma de consultar los ingredientes que posee cada fumador.
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//Definición de mutex y variable condicional
pthread_mutex_t cerrojo;
pthread_cond_t ingredientesMesa;  

//Inicializamos la mesa vacía
int mesa=0;

void *Agente(void *arg);
void *Fumador(void *arg);
int generaIngrediente();

int main(int argc, char *argv[]){
    pthread_t f1, f2, f3, a1;
    int i1 = 1, i2 = 2, i3 = 3;

    pthread_mutex_init(&cerrojo, NULL);
    pthread_cond_init(&ingredientesMesa, NULL);
   
    pthread_create(&f1, NULL, Fumador, &i1);
    pthread_create(&f2, NULL, Fumador, &i2);
    pthread_create(&f3, NULL, Fumador, &i3);
    pthread_create(&a1, NULL, Agente, NULL);

    pthread_join(f1, NULL);
    pthread_join(f2, NULL);
    pthread_join(f3, NULL);
    pthread_join(a1, NULL);

    pthread_mutex_destroy(&cerrojo);
    pthread_cond_destroy(&ingredientesMesa);

    exit(0);
}

void *Agente(void *arg){
    int i1, i2;
    while(1){
        //Genera dos ingredientes aleatorios [1-3]
        i1=generaIngrediente();
        i2=generaIngrediente();
        //(fuerza que los ingredientes sean diferentes)
        while(i1==i2)
            i2=generaIngrediente(); 
        printf("Agente: quiero dejar %d %d en la mesa.\n", i1, i2);

        /*
        Protege con un cerrojo la zona en la que accede 
        a la mesa para consultar y modificar
        */
        pthread_mutex_lock(&cerrojo);
        /*
        Si la mesa tiene algún ingrediente, el agente 
        espera a que le avisen liberando el cerrojo
        */
        if (mesa != 0) 
            pthread_cond_wait(&ingredientesMesa, &cerrojo); 
        /*
        Cuando me avisen de que no quedan ingredientes 
        en la mesa, pongo los ingredientes que tengo en la mesa
        */
        mesa=i1+i2;
        printf("Agente: pongo %d %d en la mesa.\n", i1, i2);
        //Libera el cerrojo al salir de la zona protegida
        pthread_mutex_unlock(&cerrojo);
    }
    //Sale del hilo (si no fuese while(1))
    pthread_exit(0);  
}

void *Fumador(void *arg) { 
    /*
    Cada fumador tiene un ingrediente, este ingrediente
    se coge del parámetro pasado en la inicialización del hilo
    Para coger el puntero a entero, casteamos el puntero void 
    a puntero a entero
    */
    int *miIngrediente = (int *)arg;
    while(1){
        /*
        Protege con un cerojo la zona de código en la que accede 
        a la variable mesa para consultar o para modificarla
        */
        pthread_mutex_lock(&cerrojo); 
        /*
        Si en la mesa están los ingredientes que necesita para 
        fumar (1+2+3 = 1+3+2 = 2+3+1 = 6) entonces el fumador podrá 
        fumar cuando sume 6. 
        
        Si es así, coge los ingredientes, fuma y avisa al 
        agente y libera el cerrojo.
        */
        if(mesa+(*miIngrediente) == 6){
            printf("Fumador: tengo %d y cojo los %d que necesito para tener %d.\n", (*miIngrediente), mesa, mesa+(*miIngrediente));
            mesa = 0;
            pthread_mutex_unlock(&cerrojo);
            pthread_cond_signal(&ingredientesMesa);
        }else
        /*
        si no ha podido coger los ingredientes, libera el cerrojo 
        sin avisar al agente para que no trabaje si ya hay 
        ingredientes. Alguien tiene que fumar.
        */
            pthread_mutex_unlock(&cerrojo);
    }
    //Sale del hilo (si no fuese while(1))
    pthread_exit(0);
}    
/*
Función que devuelve un numero aleatorio entre 1 y 3
*/
int generaIngrediente(){
    return rand()%3+1;
}