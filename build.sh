#!/bin/bash

mkdir -p bin
cd bin

zcc +zx -vn -startup=31 -clib=sdcc_iy @../tanchik.lst -o tanchik -create-app

cd ..

