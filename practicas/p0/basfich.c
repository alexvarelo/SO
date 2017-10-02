#include <stdio.h>
#include <stdlib.h>

int main()
{

FILE *archivo1, *archivo2;
char c;
char nombreArchivo[32];
printf("Archivo de entrada: ");
scanf("%s", &nombreArchivo);
//printf("%s", nombreArchivo);
archivo1=fopen(nombreArchivo,"r");
archivo2=fopen("copia.txt","w");

if ((archivo1==NULL)||(archivo2==NULL))

printf("Error al abrir ficheros");

else

{

	while((c=getc(archivo1))!=EOF)
	{

		putc(c,archivo2);  
	}


if (fclose(archivo1)!=0)

printf("Error al cerrar fichero prueba");

if (fclose(archivo2)!=0)

printf("Error al cerrar fichero copia");

} 
exit(0);

}
