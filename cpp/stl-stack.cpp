//------------------------------------------------
// file.........: list.cpp
// description..: list ADT - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <stdexcept>

using namespace std;


class List
{

public:

  int size()
  {
    return count;
  }

  bool isEmpty()
  {
    return count == 0; 
  }

  void insert(int index, int value)
  {
   //? if (items != nullptr) 
  }

  int get(int index)
  {
    if (index < 0) || index > (count-1))
      throw std::out_of_range("Invalid Index received; index=" + index);

    return items[i];
  }


  List(): count(0), items(nullptr){}

  ~List()
  {
    if (items != nullptr)
    {
      delete [] items;
      items = nullptr;
    }
  }

  List(const List & other)
  {
    copy(other);
  }

  List & operator=(const List & other)
  {
    if(*this != other)
    {
      copy(other);
    }

    return *this;
  }

private:
  int count;
  int * items

  void copy(const List & other)
  {
    if (items != nullptr)
      delete [] items;

    this->count = other.count;
    this->items = new int[other.count];

    for(auto i=0; i < this->count; ++i)
      items[i] = other.items[i];
  }

};


void showIt(stack<int, list<int>>  s)
{
  while(!s.empty())
  {
    cout << s.top() << " ";
    s.pop();
  }
	cout << endl;
}

int main() 
{

  //using different underline containers

  //i) queue from a list
  cout << endl << ">>>>> create a stack from a list..." << endl;
  cout << ">>>>> initial stack..." << endl;
  list<int> l0{1,2,3,4,5,6,7};
  stack<int, list<int>> s0(l0);
  showIt(s0);

  s0.push(8);
  s0.push(9);
  
  cout << ">>>>> changed stack..." << endl;
  showIt(s0);
  	
	return 0;
}

