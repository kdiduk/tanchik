#!/bin/bash

# origin of the game binary
ZORG=25000

mkdir -p bin
cd bin

zcc +zx -startup=31 -clib=sdcc_iy @../tanchik.lst \
	-zorg=${ZORG} -pragma-include:../zpragma.inc -o tanchik

appmake +zx -b tanchik_CODE.bin -o tanchik.tap \
	--blockname tanchik --org ${ZORG}

cd ..

