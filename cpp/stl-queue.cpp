//------------------------------------------------
// file.........: stl-queue.cpp
// description..: queue - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <vector>
#include <list>
#include <queue>

using namespace std;

/*
	queue:
  -this is a container adapter
  -uses an underline container
  -implements a FIFO queue
   ..push on the back
   ..pop from the front
*/

void showIt(queue<int, list<int>>  q)
{

  while(!q.empty())
  {
    cout << q.front() << " ";
    q.pop();
  }
	cout << endl;
}

int main() 
{

  //using different underline containers

  //i) queue from a list
  cout << endl << ">>>>> create a queue from a list..." << endl;
  cout << ">>>>> initial queue..." << endl;
  list<int> l0{3,4,5,6,7};
  queue<int, list<int>> q0(l0);
  showIt(q0);

  q0.push(8);
  q0.push(9);
  q0.pop();
  cout << ">>>>> changed queue..." << endl;
  showIt(q0);
  	
	return 0;
}

