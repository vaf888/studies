#!/usr/bin/env python3

""" Threads returning values - subclass it!"""

import timeit

import time
import random

import threading

class RandomSlowFunction(threading.Thread):
  def __init__(self, name):
    super().__init__()
    self.name=name

  #this run method is called by the start method from threading
  #it is required, when sub-classing threads
  def run(self):
    self.duration = random.uniform(2,4)
    print()
    print(f'>>>>>start of {self.name} -> sleeping for {self.duration:.2} seconds')
    time.sleep(self.duration)


#-----------------------------------------------------
def main():

  print("____________________")
  start_time = time.time()
  #print (f'\nstart_time={start_time:.3}')  

  threads=[]

  for i in range(5):
    thread = RandomSlowFunction(f'function-{i}',)
    thread.start() # will call my run method (class)
    threads.append(thread)

  for thread in threads:
    thread.join()

  elapsed_time = time.time() - start_time
  print(f'\n>>>>>elapsed time={elapsed_time:.3}')
  print(f'\n>>>>>total durations={sum(thread.duration for thread in threads):.3}')
  print(f'\n>>>>>longest time={max(thread.duration for thread in threads):.3}')
  print(f'\n>>>>>shortest time={min(thread.duration for thread in threads):.3}')



#-----------------------------------------------------
if __name__ == "__main__":
  main()
