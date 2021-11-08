#!/usr/bin/env python3

""" Threads critical regions """

import timeit

import time
import random

import threading

#create a dictionary such as:
#{0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
counter = {x: 0 for x in range(10)}

#keep updated counter in counter[0]
def plus_many():
  for _ in range(100_000):
    counter[0] += 1

#-----------------------------------------------------
def main():

  print("____________________")
  for _ in range(10):
    plus_many()

  print(f'\n>>>>>result={counter[0]}')
  print(f'>>>>>counter={counter}')


#-----------------------------------------------------
if __name__ == "__main__":
  main()
