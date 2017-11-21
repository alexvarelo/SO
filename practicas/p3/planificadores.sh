#!/bin/bash

# NO ARGUMENTOS

# DEBE PREGUNTAR AL USUARIO DOS COSAS: 
    # 1)Que fichero se desea simular. Se debe comprobar si existe y si es un fichero regular. Sino se volverá a preguntar

    # 2)Numero maximo de CPUS. Este numero no debera ser mayor que 8. Si es mayor se informará al usuario del error y se le volverá a preguntar.

MAX_CPU=8
MIN_CPU=1

echo "Introduzca el nombre del fichero que desea simular: "
read nomFichero
#echo $nomFichero 

while [ ! -f $nomFichero ]; do
    echo "¡¡¡El fichero $nomFichero no existe!!!"
    echo "Introduzca de nuevo el nombre del fichero: "
    read nomFichero
    #echo "Nuevo nomFichero ahora es: $nomFichero" 
	
done


echo "Introduzca el numero max de CPUS: "
read numMaxCPUs #No debe ser mayor que 8 ni menor que 1 (gt: mayor que) (le : menor o igual)


while [ $numMaxCPUs -gt $MAX_CPU ] || [ $numMaxCPUs -lt $MIN_CPU ]; do
    echo "¡¡¡El numero $numMax no es valido(deber estar entre 1 y 8)!!!"
    echo "Introduzca de nuevo el numero: "
    read numMaxCPUs
    #echo "Nuevo numero ahora es: $numMax" 
	
done

if [ -d resultados ]; #Si existe, lo borro
then 
 rm -r resultados
fi
mkdir resultados

#for nameSched in "${listaDeSchedulersDisponibles[@]}" ; #Recorre el array
for nameSched in `./schedsim/schedsim -L | tail -n 4`
do
	echo "nombre sched por el que va: $nameSched "
	
	for i in $(seq 1 $numMaxCPUs); #ambos num estan incluidos
	do
		echo "vuelta numero: $i"

		./schedsim/schedsim -i $nomFichero -n $i -s $nameSched
		
		for ((j=0;j<i;j++)); do
		  mv "CPU_$j.log" "resultados/$nameSched-CPU-$j.log" #muevo
		  #generar gŕafica
		  cd gantt-gplot
		  ./generate_gantt_chart "../resultados/$nameSched-CPU-$j.log"
	 	  cd ..
                done
	done
done


