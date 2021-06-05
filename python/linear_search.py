#!/usr/bin/env python3
#-----------------------------------------------------
def linear_search(list, key):
  """linear search implementation"""
  for i, item in enumerate(list):
    #print("DEBUG: item=",item," key=",key, " i=",i)
    if(item == key):
      return i
  return -1

#-----------------------------------------------------
def binary_search(list, key):
  """list must be sorted"""
  right = len(list) -1;
  left = 0

  while left <= right:
    middle = (int)((right + left)/2)

    if list[middle] == key:
      return middle
    elif list[middle] > key:
      right = middle - 1
    else:
      left = middle + 1

  return -1

def main():
  l = ["this", "is",  "a",  "new", "test",  "only"]
  key="test"
  print("____________________")

  expected = 4
  result = linear_search(l,key)
  assert expected == result
  print("OK - result=", result)

  print("____________________")
  l=[1,3,5,7,9,11]
  key=9
  expected = 4
  result = binary_search(l, key)
  assert expected == result
  print("OK - result=", result, " key=", key, " l[result]=",l[result])


  print("____________________")
  key=1
  expected = 0
  result = binary_search(l, key)
  assert expected == result
  print("OK - result=", result, " key=", key, " l[result]=",l[result])
  
  print("____________________")
  key=11
  expected = 5
  result = binary_search(l, key)
  assert expected == result
  print("OK - result=", result, " key=", key, " l[result]=",l[result])




if __name__ == "__main__":
  main()
