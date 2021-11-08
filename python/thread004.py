#!/usr/bin/env python3

""" Threads critical regions + race condition """

import timeit

import time
import random

import threading

#create a dictionary such as:
#{0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
counter = {x: 0 for x in range(10)}

#keep updated counter in counter[0]
def plus_many():
  start = counter[0]
  for _ in range(100_000):
    #time.sleep(1)
    counter[0] += 1

  print(f'>>>>>from start={start} to end={counter[0]}')


#-----------------------------------------------------
def main():

  print("____________________")

  threads=[]

  for _ in range(10):
    thread = threading.Thread(target=plus_many)
    thread.start()
    threads.append(thread)

  for thread in threads:
    thread.join()


  #counter[0] should be 1000.000 but, due to race condition it is not
  print(f'\n>>>>>result={counter[0]}')

  print(f'>>>>>counter={counter}')


#-----------------------------------------------------
if __name__ == "__main__":
  main()
