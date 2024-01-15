#!/bin/bash
mkdir -p objects
gcc -fPIC -c *.c
mv *.o ./objects/
gcc -shared -Wl,-soname,liball.so -o liball.so ./objects/*.o
