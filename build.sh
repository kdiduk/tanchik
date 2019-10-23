#!/bin/bash

mkdir -p bin
zcc +zx -vn -startup=31 -clib=sdcc_iy src/main.c src/tank_sprite.asm -o bin/tank -create-app

