#! /usr/bin/env bash
rm -f ../bin/%1*.*
gcc -Wa,-adhln -g -Wall $1.cpp -std=c++2a -pthread -lstdc++ -o ../bin/$1

 
