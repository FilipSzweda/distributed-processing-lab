#!/bin/bash
gcc -c  -Wall -fPIC -D_GNU_SOURCE add.c
gcc add.o -shared -o lib_add.so

gcc -c example.c -o example.o
gcc example.o -L. -l_add -o result.out
