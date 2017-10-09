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
../mytar -cf filetar.mtar file1.txt file2.txt
mkdir out
cd out
../../mytar -xf ../filetar.mtar

DIFF=$(diff file1.txt ../file1.txt) 
if [ "$DIFF" != "" ] 
then
    cd ../..
    echo "file1.txt no son iguales"
    exit 1
fi

DIFF=$(diff file2.txt ../file2.txt) 
if [ "$DIFF" != "" ] 
then
    cd ../..
    echo "file2.txt no son iguales"
    exit 1
fi
cd ../..
echo Correct
exit 0
