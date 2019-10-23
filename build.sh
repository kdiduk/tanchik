#!/bin/bash

mkdir -p bin
cd bin

mkdir -p sprites
png2sp1sprite.py ../assets/player.png -b -i player_sprite > sprites/player.asm

zcc +zx -vn -startup=31 -clib=sdcc_iy ../src/main.c sprites/player.asm -o tanchik -create-app

cd ..

