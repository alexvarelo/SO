//incluye libreria con funciones de I/O necesarias para interactuar con el usuario
#include <stdio.h>
//Incluye libreria con las funciones del SO para terminar el proceso
#include <stdlib.h>

int main()
{
/*
Crea dos punteros de tipo FILE, un char para recorrer caracteres, 
un array de char para el nombre del fichero y un entero para contar 
el tamaño del fichero
*/
FILE *archivo1, *archivo2;
char c;
char *nombreArchivo;
int fsize = 0;

/*
Pide el nombre del fichero a medir (max 32 caracteres)
*/
printf("Archivo de entrada: ");
scanf("%ms", &nombreArchivo);

//printf("%s", nombreArchivo);

/*
Abre los ficheros en con permisos de escritura y el segundo 
con permisos de escritura apuntando a las direcciones de 
comienzo de cada uno de ellos
*/
archivo1=fopen(nombreArchivo,"r");
archivo2=fopen("info.txt","w");

/*
Comprueba que existan los dos ficheros (si una de las direcciones 
de memoria conitene un valor nulo, saldrá de la ejecución con 
error de apertura de ficheros)
*/
if (archivo1==NULL)

printf("Error al abrir ficheros");

/*
En caso de abrir ambos ficheros correctamente
*/
else

{
	/*
	Recorre caracter a caracter hasta el final del fichero (EOF). 
	[Modificación: ya no guardamos el caracter en c] 
	*/
	while((getc(archivo1))!=EOF)
	{
		/*
		Cada caracter que encontremos sumamos un Byte
		*/
		fsize+=1;
	}
	/*
	Escribimos en el fichero el nombre del archivo y su tamaño
	*/
	fprintf(archivo2, "%s [%d]Bytes", nombreArchivo, fsize);
	free(nombreArchivo);
/*
Cerramos los dos ficheros avisando si ha habido algún error
*/
if (fclose(archivo1)!=0)
printf("Error al cerrar fichero prueba");
if (fclose(archivo2)!=0)
printf("Error al cerrar fichero copia");

} 
/*
Terminamos el proceso
*/
exit(0);

}
