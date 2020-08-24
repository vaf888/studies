//------------------------------------------------
// file.........: doubleLocking.cpp
// description..: concurrency + double locking studies
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
#include <iterator>
#include <algorithm>  // for std::find
#include <utility>    // make_pair
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;

void message(string s)
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/
using namespace std;

struct widget
{ //...
};

// we want the global widget object (instance) - only one copy
//widget* instance = nullptr; - error - must be atomic !!

atomic<widget*> pInstance{nullptr}; //OK
mutex wmutex;

/*
  initial version
*/
widget* getInstanceV0() 
{
  if (pInstance == nullptr) 
  {
    // ERROR: if NOT ATOMIC -> interleaving might occurs here, when still 
    //        getting the lock
    //        so, instance could not be nullptr anymore!!!

    //CORRECTION: pInstance MUST be atomic
    // The shared variable is atomic, so no race condition (to generate an error)
    lock_guard lock(wmutex); // lock_guard<mutex> lock(wmutex) in pre C++17    

    if (pInstance == nullptr)
      pInstance = new widget();
  }
  return pInstance;
}

/*
  a bit faster version using temporary var
*/
widget* getInstanceV1() 
{
  widget * p = pInstance;

  if (p == nullptr) 
  {
    // ERROR: if NOT ATOMIC -> interleaving might occurs here, when still 
    //        getting the lock
    //        so, instance could not be nullptr anymore!!!

    //CORRECTION: pInstance MUST be atomic
    // The shared variable is atomic, so no race condition (to generate an error)
    lock_guard lock(wmutex); //enter the critical section

    if ((p = pInstance) == nullptr)
      pInstance = p = new widget();
  } // release the lock - end of crit. sec.

  return p;
}

/*
  using :
  -magic statics
   ..they are thread safe initialize local function statics
   ..they are designed to initialize them the first time controls pass
     through them (any thread)
   ..compiler dos the double locking behind the scenes
   ..executed only once (if 2 threads come together, it will be sinchronized)
*/
widget& getInstanceV2() 
{
  static widget instance;

  return instance;
}



int main() 
{

  auto newInstanceV0 = getInstanceV0();
  cout << "instance=" << newInstanceV0 << endl;

  pInstance=nullptr;

  auto newInstanceV1 = getInstanceV1();
  cout << "instance=" << newInstanceV1 << endl;

  auto newInstanceV2 = getInstanceV2();
  cout << "instance=" << &newInstanceV2 << endl;


	return 0;

}

