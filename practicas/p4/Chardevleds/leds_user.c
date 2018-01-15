#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include<pthread.h>

void *trabajo(void *arg);
void jugarConHilos();
void circulo();
void bajada();
void secuencia();
int devfile;
pthread_t tid[3]; 

int main(int argc,char *argv[]){
    devfile = open(argv[1],O_WRONLY|O_TRUNC|O_CREAT);
    /*
    circulo();
    bajada();
    secuencia();
    */
    jugarConHilos();
    close(devfile);
    return 0;
}

void jugarConHilos(){
    int i = 0;
    int err;

    while(i < 3)  //Queremos crear 2 hilos
    {
        err = pthread_create(&(tid[i]), NULL, trabajo, NULL);
        if (err != 0)
            printf("\nError al crear el hilo :");
        else
            printf("\n Hilo creado!\n");

        i++;
    }
    
    (void) pthread_join(tid[0], NULL);
    (void) pthread_join(tid[1], NULL);
    (void) pthread_join(tid[2], NULL);
}

void *trabajo(void *arg)
{
    int i = 0;
    pthread_t id = pthread_self();
    for(i=0; i<100; i++)
    {
     	if(pthread_equal(id,tid[0]))
            write(devfile,"001",3);
        else if(pthread_equal(id,tid[1]))
            write(devfile,"002",3);
    	else
            write(devfile,"003",3);    
        sleep(1);
    }
    return NULL;
}

void circulo(){
    for (char c = '1' ; c <= '3' ; c++) {
        write(devfile, &c, 1);
        sleep(1);
        c=(c=='3')?'0':c;
    }
}

void bajada(){
    for (char c = '3' ; c >= '1' ; c--) {
        write(devfile, &c, 1);
        sleep(1);
    }
}

void secuencia(){
    char sec[15]="020130200301210";
    for (int i=0;i<15;i++){
        write(devfile,&sec[i],3);
        sleep(1);
    }
}
