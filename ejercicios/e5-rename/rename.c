#include <stdio.h>
int main () {
//printf((rename("viejo.txt","nuevo.txt")==0)?"Fichero renombrado con exito":"Error: no se puede renombrar el fichero.");

 if(rename("viejo.txt","nuevo.txt")==0)
  printf("Fichero renombrado con exito");
 else
  printf("Error: no se puede renombrar el fichero");
 return(0);
}