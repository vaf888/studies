#! /usr/bin/env bash
gcc -g -Wall -Wpedantic $1.cpp -std=c++17 -pthread -lstdc++ -o $1
 
