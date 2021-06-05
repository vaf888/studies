#! /usr/bin/env bash
rm -f ../bin/%1*.*
#gcc -g -Wall -Wextra -Wpedantic $1.cpp -std=c++2a -pthread -lstdc++ -ltbb 
gcc -g -c test000.cpp -o test000.o 

 
