#!/bin/bash

# Origin of the game binary. Default value is 32768.
# For other values, add `-zorg=${ZORG}` option to `zcc` command.
ZORG=32768

mkdir -p bin
cd bin

zcc +zx -Wall -startup=31 -clib=sdcc_iy @../tanchik.lst \
	-I../include -pragma-include:../zpragma.inc -o tanchik

# Add option `--audio` to produce wav-tape
appmake +zx -b tanchik_CODE.bin -o tanchik.tap \
	--blockname tanchik --org ${ZORG}

cd ..

echo "Build finished"
