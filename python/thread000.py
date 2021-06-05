#!/usr/bin/env python3

import timeit

import time
import random


#-----------------------------------------------------
def f00():
  """timing simple operation"""
  res = timeit.timeit('a*b', setup='a=3.5; b=2.0', number=5)
  print("res=",res)

#-----------------------------------------------------
def f01():
  """timing internet access"""
  res = timeit.timeit('requests.get("http://www.python.com")', 
    setup='import requests', number=5)
  print("res=",res)

#-----------------------------------------------------
def random_slow_function(name):
  duration = random.uniform(2,4)
  print()
  print(f'>>>>>start of {name} -> sleeping for {duration:.2} seconds')
  time.sleep(duration)
  print(f'>>>>>End of {name}')


#-----------------------------------------------------
def main():

  print("____________________")
  f00()

  print("____________________")
  f01()

  print("____________________")
  start_time = time.time()

  print (f'\nstart_time={start_time:.3}')  
  
  for i in range(5):
    random_slow_function(f'function-{i}')
    
  elapsed_time = time.time() - start_time

  print (f'\nelapsed time={elapsed_time:.3}')

#-----------------------------------------------------
if __name__ == "__main__":
  main()
