#!/bin/bash

echo "Creando carpeta termporal ./tmp ..."
rm -Rf tmp
mkdir tmp

echo "Copiando fuseLib.c y myFS.h a ./tmp y ./mount-point ..."
cp src/fuseLib.c mount-point/fuseLib.c
cp src/fuseLib.c tmp/fuseLib.c

cp src/myFS.h mount-point/myFS.h
cp src/myFS.h tmp/myFS.h

echo "Mostrando diferencias del primer fichero fuseLib.c:"
if diff tmp/fuseLib.c mount-point/fuseLib.c
then echo "[IGUALES]"
else echo "[DIFERENTES]"
fi

echo "Modificamos el tamaño de fuseLib.c en ./mountpoint y ./tmp"
truncate mount-point/fuseLib.c -s -1
truncate tmp/fuseLib.c -s -1
echo "Mostrando diferencias del primer fichero fuseLib.c:"
if diff tmp/fuseLib.c mount-point/fuseLib.c
then echo "[IGUALES]"
else echo "[DIFERENTES]"
fi

echo "Copiamos un tercer fichero de texto test/file1.txt"
cp test/file1.txt mount-point/file1.txt

echo "Mostrando diferencias del tercer fichero file1.txt:"
if diff test/file1.txt mount-point/file1.txt
then echo "[IGUALES]"
else echo "[DIFERENTES]"
fi

echo "Modificamos el tamaño del segundo en ./mount-point y ./tmp"
truncate mount-point/myFS.h -s +5
truncate tmp/myFS.h -s +5

echo "Mostrando diferencias del segundo fichero myFS.h:"
if diff tmp/myFS.h mount-point/myFS.h
then echo "[IGUALES]"
else echo "[DIFERENTES]"
fi

echo "Creando carpeta con mkdir"
ls -la mount-point