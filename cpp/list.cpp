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

  /*
  ---------------------------------------------
  */
  int size()
  {
    return count;
  }

  /*
  ---------------------------------------------
  */
  bool isEmpty()
  {
    return count == 0; 
  }

  /*
  ---------------------------------------------
  */
  void insert(int index, int value)
  {
    checkBounds(index);

    int * oldItems = items;

    count++;

    items = new int[count];

    int oldIndex=0;
    for(auto i=0; i < count; ++i)
    {
      if (i == index)
      {
        items[i] = value;
      }
      else
      {
        items[i] = oldItems[oldIndex++]; 
      }
    }

    delete [] oldItems;
  }

  /*
  ---------------------------------------------
  */
  int search(int value)
  {
    if (isEmpty())
      return -1;

    for(auto i=0; i < count; ++i)
    {
      if (items[i] == value)
        return i;
    }

    return -1;
  }

  /*
  ---------------------------------------------
  */
  int get(int index)
  {
    checkBounds(index);
    return items[index];
  }

  /*
  ---------------------------------------------
  */
  List(): count(0), items(nullptr){}

  /*
  ---------------------------------------------
  */
  ~List()
  {
    if (items != nullptr)
    {
      delete [] items;
      items = nullptr;
    }
  }

  /*
  ---------------------------------------------
  */
  List(const List & other)
  {
    items = nullptr;
    count=0;
    copy(other);
  }

  /*
  ---------------------------------------------
  */
  List & operator=(const List & other)
  {
    if(this != &other)
    {
      copy(other);
    }

    return *this;
  }

  /*
  ---------------------------------------------
  */
  int& operator[](int index)
  {
    checkBounds(index);

    return items[index];
  }

  friend ostream& operator << (ostream& os, const List & l);

private:
  int count;
  int * items;

  /*
  ---------------------------------------------
  */
  void copy(const List & other)
  {
    if (items != nullptr)
      delete [] items;

    this->count = other.count;
    this->items = new int[other.count];

    for(auto i=0; i < this->count; ++i)
      items[i] = other.items[i];
  }

  /*
  ---------------------------------------------
  */
  void checkBounds(int index)
  {
    if ((index < 0) || (index > count))
      throw std::out_of_range("Invalid Index received; index=" + index);
  }

};

ostream& operator << (ostream& os, const List & l)
{
  os << ">>>>>list content:" << endl;

  for(auto i=0; i < l.count; ++i)
  {
    os << l.items[i] << " ";
  }
  os << endl;

  return os;
}

int main() 
{

  List l0{};
  cout << "size=" << l0.size() << endl;
  l0.insert(0,11);
  l0.insert(1,22);
  l0.insert(2,33);
  l0.insert(3,44);
  l0.insert(4,55);
  l0.insert(5,66);
  l0.insert(6,77);
  //l0[6]=88;
  cout << endl << "_______________" << endl;
  cout << ">>>>> list l0" << endl;
  cout << "size=" << l0.size() << endl;
  cout << l0;

  // copy const.
  cout << endl << "_______________" << endl;
  cout << ">>>>> list l1" << endl;
  List l1 = l0;
  cout << "size=" << l1.size() << endl;
  cout << l1;

  // assign. operator
  cout << endl << "_______________" << endl;
  cout << ">>>>> list l3" << endl;
  List l3{};
  l3.insert(0,99);
  l3 = l1;
  l3.insert(0,100);
  cout << "size=" << l3.size() << endl;
  cout << l3;
  	
	return 0;

}

