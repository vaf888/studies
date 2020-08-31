//------------------------------------------------
// file.........: iterators.cpp
// description..: stl iterators - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <stdexcept>
#include <set>
#include <iterator>
#include <forward_list> // sngle linked list type
#include <algorithm>    // for std::find


using namespace std;

/*
------------------------------------------------
*/
void message(string s)
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/
void inputIterator()
{
  /*
  double d1=0, d2=0;

  cout << "Two numeric values: " << flush;

  cin.clear();

  // def. constructor is end-of-stream
  istream_iterator<double> eos;
  istream_iterator<double> iit(cin); // stdin iteraor

  // read value (if available) + increment the iterator
  if (iit == eos)
  {
    message("no values available !!!");
  }
  else
  {
    d1 = *(iit++);
  }

  if (iit == eos)
  {
    message("no SECOND value available !!!");
  }
  else
  {
    d2 = *(iit++);
  }

  cout << "values read -> d1 = " << d1 << "; d2 = " << d2 << endl;
  */
}

/*
------------------------------------------------
*/
void outputIterator()
{

  // output stream iterator -> created with a separator " "
  // each item will be displayed using the separator
  ostream_iterator<int> itOut(cout, " ");

  for (auto i:{10,20,30,40,50})
    *(itOut++) = i;
}

/*
------------------------------------------------
*/
void forwardIterator()
{
  //forward_list
  //..are sequence containers that allow constant time insert and erase 
  //  (each element keeps information on how to locate the next element, 
  //   allowing constant time insert and erase operations, after a specific 
  //   element (even of entire ranges), but no direct random access.)
  //  operations anywhere within the sequence.
  //..are implemented as singly-linked lists
  //..are more efficient than list objects, although 
  //  they can only be iterated forwards.
  //..The main drawback of forward_lists and lists compared to 
  //  sequence containers: they lack direct access to the elements 
  //  by their position.
  std::forward_list<int> fwdList {11, 22, 44, 88};
  std::forward_list<int>::iterator it1;

  for (auto it = fwdList.begin(); it != fwdList.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

}

/*
------------------------------------------------
*/
void bidirectionalIterator()
{
  std::set<int> s{1,2,3,4,5,6};

  cout << ">>>>>from start to end: " << endl;
  for (auto it=s.begin(); it != s.end(); ++it)
    cout << *it << " ";
  cout << endl;

  cout << ">>>>>from end to start: " << endl;
  for (auto it=s.end(); it != s.begin();)
    cout << *(--it) << " ";
  cout << endl;

  cout << ">>>>>from end to start using rbegin() and rend() - reverse iter.: " << endl;
  for (auto it=s.rbegin(); it != s.rend(); ++it)
    cout << *it << " ";
  cout << endl;

}

/*
------------------------------------------------
*/
int main()
{
  cout << ">>>>>input iterator..." << endl;
  inputIterator();

  cout << endl;
  cout << ">>>>>output iterator..." << endl;
  outputIterator();

  cout << endl;
  cout << ">>>>>forward iterator..." << endl;
  forwardIterator();

  cout << endl;
  cout << ">>>>>bidirectional iterator..." << endl;
  bidirectionalIterator();

  cout << endl;

  return 0;
}



