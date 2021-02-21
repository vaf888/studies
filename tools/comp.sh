#! /usr/bin/env bash
rm -f ../bin/%1*.*
gcc -g -Wall -Wextra -Wpedantic -fsanitize=address $1.cpp -std=c++2a -pthread -lstdc++ -o ../bin/$1

 
