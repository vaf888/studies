//------------------------------------------------
// file.........: future.cpp
// description..: async. operations - studies
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
#include <future>

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


/*
  a bit faster version using temporary var
*/

/*
--------------------------------------------------
  main
--------------------------------------------------  
*/

int main()
{

  std::future<double> fut = 
    std::async(std::launch::async,
               [](){return 4.2d;} // long calc. async.
              );

  // task is now running in background

  //get() - will block until value is available
  double result = fut.get();

  cout << endl;
  cout << "_________________________________" << endl;
  cout << ">>>>>future (1) ..." << endl;
  cout << "result=" << result << endl;
  cout << endl;

  return 0;
}


