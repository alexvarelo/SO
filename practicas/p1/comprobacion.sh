#!/bin/bash
if [ -f mytar ];
then 
    echo El fichero existe
    if [ -x mytar ];
    then
    echo El fichero es ejecutable
    else
    echo No ejecutable
    fi
else
echo No existe
fi

if [ -d tmp ];
then
    echo La carpeta tmp existe
    echo Borrando tmp
    rm -r tmp
else
    echo La carpeta tmp no existe
fi
mkdir tmp
cd tmp
echo Hello world! > file1.txt
head /etc/passwd > file2.txt
head -c1024 /dev/urandom > file3.dat
../mytar -cf filetar.mtar file1.txt file2.txt file3.dat
mkdir out
cd out
../../mytar -xf ../filetar.mtar

if diff file1.txt ../file1.txt && diff file2.txt ../file2.txt && diff file3.dat ../file3.dat
then 
    cd ../..
    echo Correct
    exit 0
else 
    cd ../..
    echo Los ficheros no son iguales
    exit 1    
fi