#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <sys/types.h> 

// getchar() se utiliza principalmente para parar la ejecucion y poder hacer
// cat /proc/PID/maps
// Basado en programa de Roger Qiu https:\\gits.github.com/CMCDragonkai

void * thread_func (void * arg) {

    int variable_local_hilo; 	
    printf("Antes de hacer malloc dentro del hilo\n");
    getchar();
    char * addr = (char *) malloc(1000);
    printf("Direccion de memoria donde esta almacenado addr dentro del hilo ::%X\n", addr);
    printf("Direccion de memoria donde esta almacenado variable_local::%X\n", &variable_local_hilo);
    scanf("Introduce un valor para addr:: %s", addr);
    variable_local_hilo=addr;
    printf("Despues de hacer malloc y antes de hacer free, dentro del hilo\n");
    getchar();
    free(addr);
    printf("Despues de hacer free en el hilo\n");
    getchar();

}

int main () {

    char * addr;
    int variable_local;	
    printf("Ejemplo para entender el mapa de memoria::%d\n", getpid());
    printf("Antes de hacer malloc\n");
    getchar();
    addr = (char *) malloc(1000);
    printf("Direccion de memoria donde esta almacenado addr::%X\n", addr);
    printf("Direccion de memoria donde esta almacenado variable_local::%X\n", &variable_local);
    scanf("Introduce un valor para addr:: %s", addr);
    variable_local=addr;
    printf("Despues del malloc y antes del free\n");
    getchar();
    free(addr);
    printf("Despues del free en main y antes de llamar al hilo\n");
    getchar();

    
    pthread_t thread_1;
    // pthread
    int pthread_status;

    pthread_status = pthread_create(&thread_1, NULL, thread_func, NULL);
    
    if (pthread_status != 0) {
        printf("Thread creation error\n");
        return -1;
    }

    
    void * thread_1_status;

    pthread_status = pthread_join(thread_1, &thread_1_status);
    
    if (pthread_status != 0) {
        printf("Thread join error\n");
        return -1;
    }

    return 0;

}
