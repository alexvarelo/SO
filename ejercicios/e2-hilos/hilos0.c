#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *trabajo(void *arg);

char mensaje[] = "Descubriendo hilos"; //Variable global

pthread_t tid; //tid es el identificador de hilo (threadID)

int main(void)
{

    printf("El mensaje original es: %s\n", mensaje);
    int err;
//Pasamos a crear un hilo que modifique la variable global mensaje 
   err = pthread_create(&tid, NULL, trabajo, NULL);
  if (err != 0)
      printf("\nError al crear el hilo :[%d]", strerror(err));
  else
      printf("\n Hilo creado!\n");

    sleep(5);
    printf("El mensaje modificado por el hilo es: %s\n", mensaje);
    
    return 0;
}

void *trabajo(void *arg)
{
  printf("Se esta ejecutando el hilo\n");
  sleep(1);
  strcpy(mensaje, "¡Descubierto!");
  pthread_exit(NULL);
}
